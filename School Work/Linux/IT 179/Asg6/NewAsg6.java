/**
 * 10/23/13 
 * @author Andrew Hinh
 */
import myUtil.*;

import java.text.DecimalFormat;
import java.util.*;
import java.io.*;

public class NewAsg6 {

	public static void main(String[] args) {

		Scanner in;
		String[] equations,postFix;
		AStack operands;
		AStack values;
		DecimalFormat nf = new DecimalFormat("#0.####");

		try {
			in = new Scanner(new File("/home/cli2/public/IT179/arithExps.txt"));

			//declare array with size equal to number of lines as equation
			equations = new String[20];
			postFix = new String[20];
			for (int i = 0; i < postFix.length; i++) {
				postFix[i] = "";
			}


			int counter = 0;
			//load all lines into equations String array
			while(in.hasNext()) {
				equations[counter++] = in.nextLine();
			}

			//begin converting each line to postfix notation
			int currentLine = 0;
			while(currentLine < equations.length) {
				operands = new AStack<String>(equations[currentLine].length());
				values = new AStack<Double>(equations[currentLine].length());

				int index = 0;
				//load same line with operands having spaces into equations
				String spacedLine = "";
				while (index < equations[currentLine].length()) {

					if (equations[currentLine].charAt(index) == '('
							|| equations[currentLine].charAt(index) == ')'
							|| equations[currentLine].charAt(index) == '+'
							|| equations[currentLine].charAt(index) == '-'
							|| equations[currentLine].charAt(index) == '*'
							|| equations[currentLine].charAt(index) == '/'
							|| equations[currentLine].charAt(index) == '^') {
						spacedLine += (" " + equations[currentLine].charAt(index) + " ");
					} else {
						spacedLine += equations[currentLine].charAt(index);
					}
					index++;
				}
				equations[currentLine] = spacedLine;
				//System.out.println(equations[currentLine]); //tests that new array carries space beforehand
				currentLine++;				
			}

			currentLine = 0;
			index = 0;
			while (currentLine < equations.length) {
				double firstNum;
				double secondNum;
				double answer;
				String symbol;

				if (equations[currentLine].charAt(index) != '('
						&& equations[currentLine].charAt(index) != ')'
						&& equations[currentLine].charAt(index) != '+'
						&& equations[currentLine].charAt(index) != '-'
						&& equations[currentLine].charAt(index) != '*'
						&& equations[currentLine].charAt(index) != '/'
						&& equations[currentLine].charAt(index) != '^') {
					values.push(Double.parseDouble(equations[currentLine].charAt(index)));

				} else {

					if (equations[currentLine].charAt(index) != '(') { // (out highest priority, always push
						operands.push(equations[currentLine].charAt(index));
					}
					if (equations[currentLine].charAt(index) != '^') {// ^ will be highest priority when looking into stack, thus push
						operands.push(equations[currentLine].charAt(index));
					}
					if (equations[currentLine].charAt(index) != '*') {
						if (!operands.empty()) {
							if (operands.peek() == '^') { // if ^ in stack, perform and push
								secondNum = values.pop();
								firstNum = values.pop();
								symbol = operands.pop();
								postFix[currentLine] += (firstNum + " " + secondNum + " " + symbol + " ");
								values.push(Math.pow(first, secondNum));
							}
							operands.push(equations[currentLine].charAt(index));
						}
						else
							operands.push(equations[currentLine].charAt(index));
					}
					if (equations[currentLine].charAt(index) != '/') {
						if (!operands.empty()) {
							if (operands.peek() == '^') { // if ^ in stack, perform and push
								secondNum = values.pop();
								firstNum = values.pop();
								symbol = operands.pop();
								postFix[currentLine] += (firstNum + " " + secondNum + " " + symbol + " ");
								values.push(Math.pow(first, secondNum));
							}
							operands.push(equations[currentLine].charAt(index));
						}
						else
							operands.push(equations[currentLine].charAt(index));
					}
					if (equations[currentLine].charAt(index) != '+') {
						if (!operands.empty()) {
							if (operands.peek() == '^') { // if ^ in stack, perform and push
								secondNum = values.pop();
								firstNum = values.pop();
								symbol = operands.pop();
								postFix[currentLine] += (firstNum + " " + secondNum + " " + symbol + " ");
								values.push(Math.pow(nf.format(first, secondNum)));
							}
							else if (operands.peek() == '*') {
								secondNum = values.pop();
								firstNum = values.pop();
								symbol = operands.pop();
								postFix[currentLine] += (firstNum + " " + secondNum + " " + symbol + " ");
								values.push(nf.format(firstNum * secondNum));
							}
							else if (operands.peek() == '/') {
								secondNum = values.pop();
								firstNum = values.pop();
								symbol = operands.pop();
								postFix[currentLine] += (firstNum + " " + secondNum + " " + symbol + " ");
								values.push(nf.format(firstNum/secondNum));
							}							
							operands.push(equations[currentLine].charAt(index));
						}						
						else
							operands.push(equations[currentLine].charAt(index));
					}
					if (equations[currentLine].charAt(index) != '-') {
						if (!operands.empty()) {
							if (operands.peek() == '^') { // if ^ in stack, perform and push
								secondNum = values.pop();
								firstNum = values.pop();
								symbol = operands.pop();
								postFix[currentLine] += (firstNum + " " + secondNum + " " + symbol + " ");
								values.push(Math.pow(nf.format(first, secondNum)));
							}
							else if (operands.peek() == '*') {
								secondNum = values.pop();
								firstNum = values.pop();
								symbol = operands.pop();
								postFix[currentLine] += (firstNum + " " + secondNum + " " + symbol + " ");
								values.push(nf.format(firstNum * secondNum));
							}
							else if (operands.peek() == '/') {
								secondNum = values.pop();
								firstNum = values.pop();
								symbol = operands.pop();
								postFix[currentLine] += (firstNum + " " + secondNum + " " + symbol + " ");
								values.push(nf.format(firstNum/secondNum));
							}							
							operands.push(equations[currentLine].charAt(index));
						}						
						else
							operands.push(equations[currentLine].charAt(index));
					}
					if (equations[currentLine].charAt(index) != ')') {
						if (!operands.empty()) {
							while (operands.peek() != '(') {
								secondNum = values.pop();
								firstNum = values.pop();
								symbol = operands.pop();
								postFix[currentLine] += (firstNum + " " + secondNum + " " + symbol + " ");
								values.push(nf.format(firstNum/secondNum));
							}

						}				
					}
					index++;	
					currentLine++;
				}
			}
		}
		catch (FileNotFoundException e) {
			System.out.println(e);
		}
	}
}
