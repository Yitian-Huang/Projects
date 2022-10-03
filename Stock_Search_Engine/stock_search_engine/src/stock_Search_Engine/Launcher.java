package stock_Search_Engine;

import java.util.Scanner;

public class Launcher {

	public static void main(String[] args) {
		//Create a new Engine.
		Engine myEng = new Engine();
		//This scanner will be used throughout the execution of the program
		//to receive command line user inputs
		Scanner in = new Scanner(System.in);
		myEng.openFile(in);
		myEng.openInterface(in);
		in.close();

	}

}
