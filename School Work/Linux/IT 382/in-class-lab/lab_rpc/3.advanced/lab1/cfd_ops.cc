#include "cf.h"
#include "cfd_fs.hh"
#include "scopeguard.hh"
#include "scopedlock.hh"

cfd_fs_dir root;
pthread_mutex_t mu;

struct eval_pathname_result {
    cfd_fs_dir *dir;
    std::string name;
};

// This function parses pathname into two parts: everything
// up to the last slash, and everything after it.  The first
// part is looked up in the file system, and must be a directory
// (otherwise, an exception is thrown).  It's returned in the
// "dir" field.  The second component is not interpreted, and
// is returned as a string in the "name" field.
//
// For example,
//    eval_pathname("foo/bar/baz")
// throws an exception if foo/bar is not a valid directory,
// and otherwise returns { d, "baz" }, where d is the cfd_fs_dir
// object for the foo/bar directory.
static eval_pathname_result
eval_pathname(char *pathname)
{
    char *pn = strdup(pathname);
    scope_guard<void, void*> cleanup(free, pn);

    /* Eat leading slashes */
    while (*pn && *pn == '/')
	pn++;

    eval_pathname_result r;
    r.dir = &root;

    char *slash;
    while ((slash = strchr(pn, '/')) != 0) {
	*slash = '\0';
	char *name = pn;
	pn = slash + 1;

	cfd_fs_node *n = r.dir->lookup(name);
	if (!n->is_a_directory())
	    throw cf_error(CFERR_NOT_A_DIRECTORY);
	r.dir = (cfd_fs_dir *) n;
    }

    r.name = pn;
    return r;
}

bool_t
cfs_null_1_svc(void *argp, void *result, struct svc_req *rqstp)
{
    return 1;
}

bool_t
cfs_read_1_svc(cfs_pathname *argp, cfs_read_res *result, struct svc_req *rqstp)
{
    scoped_pthread_lock l(&mu);
    memset(result, 0, sizeof(*result));

    try {
	eval_pathname_result pnr = eval_pathname(*argp);
	if (pnr.name == "")
	    throw cf_error(CFERR_IS_A_DIRECTORY);
	cfd_fs_node *n = pnr.dir->lookup(pnr.name);
	if (n->is_a_directory())
	    throw cf_error(CFERR_IS_A_DIRECTORY);

	cfd_fs_file *f = (cfd_fs_file *) n;
	int len = f->get_length();
	char *buf = (char *) malloc(len);
	f->read(buf, len);

	result->cfs_read_res_u.data.cfs_file_data_len = len;
	result->cfs_read_res_u.data.cfs_file_data_val = buf;
	result->errno = CFERR_NONE;
    } catch (cf_error &e) {
	result->errno = e.err();
    }
    return 1;
}

bool_t
cfs_write_1_svc(cfs_write_arg *argp, cfs_error *result, struct svc_req *rqstp)
{
    scoped_pthread_lock l(&mu);
    try {
	eval_pathname_result pnr = eval_pathname(argp->pn);
	if (pnr.name == "")
	    throw cf_error(CFERR_IS_A_DIRECTORY);
	cfd_fs_node *n = pnr.dir->lookup(pnr.name);
	if (n->is_a_directory())
	    throw cf_error(CFERR_IS_A_DIRECTORY);

	cfd_fs_file *f = (cfd_fs_file *) n;
	f->write(argp->data.cfs_file_data_val,
		 argp->data.cfs_file_data_len);
	*result = CFERR_NONE;
    } catch (cf_error &e) {
	*result = e.err();
    }
    return 1;
}

bool_t
cfs_mkdir_1_svc(cfs_pathname *argp, cfs_error *result, struct svc_req *rqstp)
{
    scoped_pthread_lock l(&mu);
    try {
	eval_pathname_result pnr = eval_pathname(*argp);
	if (pnr.name == "")
	    throw cf_error(CFERR_NAME_EXISTS);
	pnr.dir->mkdir(pnr.name);
	*result = CFERR_NONE;
    } catch (cf_error &e) {
	*result = e.err();
    }
    return 1;
}

bool_t
cfs_mkfile_1_svc(cfs_pathname *argp, cfs_error *result, struct svc_req *rqstp)
{
    scoped_pthread_lock l(&mu);
    try {
	eval_pathname_result pnr = eval_pathname(*argp);
	if (pnr.name == "")
	    throw cf_error(CFERR_NAME_EXISTS);
	pnr.dir->mkfile(pnr.name);
	*result = CFERR_NONE;
    } catch (cf_error &e) {
	*result = e.err();
    }
    return 1;
}

bool_t
cfs_delete_1_svc(cfs_pathname *argp, cfs_error *result, struct svc_req *rqstp)
{
    scoped_pthread_lock l(&mu);
    try {
	eval_pathname_result pnr = eval_pathname(*argp);
	if (pnr.name == "")
	    throw cf_error(CFERR_NO_SUCH_NAME);
	pnr.dir->remove(pnr.name);
	*result = CFERR_NONE;
    } catch (cf_error &e) {
	*result = e.err();
    }
    return 1;
}

bool_t
cfs_readdir_1_svc(cfs_pathname *argp, cfs_readdir_res *result, struct svc_req *rqstp)
{
    scoped_pthread_lock l(&mu);
    memset(result, 0, sizeof(*result));
    try {
	// Insert your readdir implementation here.
    } catch (cf_error &e) {
	result->errno = e.err();
    }
    return 1;
}

int
cfs_prog_1_freeresult(SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
    xdr_free(xdr_result, result);
    return 1;
}
