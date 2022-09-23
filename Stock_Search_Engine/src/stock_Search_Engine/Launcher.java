package stock_Search_Engine;

import java.util.Scanner;

public class Launcher {

	public static void main(String[] args) {
		Engine myEng = new Engine();
		Scanner in = new Scanner(System.in);
		myEng.openFile(in);
		myEng.openInterface(in);
		in.close();

	}

}
