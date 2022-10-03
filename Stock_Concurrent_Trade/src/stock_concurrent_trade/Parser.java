package stock_concurrent_trade;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;
import com.google.gson.Gson;
import com.google.gson.JsonParseException;
//Parser class that could be used to parse JSON and CVS files needed
//for this trade system to work.
public class Parser {
	//JSON file parser. It stores the parsed info in a Content object and returns this object.
	//Gson is used to parse JSON file
	public Content jsonParse(Scanner in, Gson gson) {
		Content content = null;
		//Loop until user provide correct filename with correct format
		while(true) 
		{
			String data = "";
			String fileName = null;
			Scanner sc = null;
			try {
				System.out.println("What is the name of the file containing the company information?");
				fileName = in.nextLine();
				File file = new File(fileName);
				sc = new Scanner(file);
				while(sc.hasNext())
				{
					data+=sc.nextLine();
				}
				content = gson.fromJson(data, Content.class);
				//Throw exception if the file is empty.
				if(content==null) {
					throw new JsonParseException("Empty file");//Scanner will be closed in catch block.
				}
				//Throw exception if the file is not formatted properly.
				for(int i=0; i< content.getData().size(); i++) {
					if(content.getDataByIndex(i).getName()==null) {
						throw new JsonParseException("Missing company name.");
					}
					else if(content.getDataByIndex(i).getTicker()==null) {
						throw new JsonParseException("Missing ticker.");
					}
					else if(content.getDataByIndex(i).getStartDate()==null) {
						throw new JsonParseException("Missing start date.");
					}
					else if(content.getDataByIndex(i).getDescription()==null) {
						throw new JsonParseException("Missing description.");
					}
					else if(content.getDataByIndex(i).getExchangeCode()==null) {
						throw new JsonParseException("Missing exchange.");
					}
					else if(content.getDataByIndex(i).getStockBrokers()==-100) {
						throw new JsonParseException("Missing stockbrokers.");
					}
				}
				System.out.println("The file has been properly read.");
				sc.close();
				return content;
				
			}catch(FileNotFoundException fnf){
				System.out.println("The file "+fileName+" could not be found.");
			}catch(JsonParseException jpe){
				System.out.println("The file "+fileName+" is not formatted properly.");
				sc.close();
			}
		}
		
	}
	//CSV file parser. An ArrayList is passed in as an argument 
	//and all the trade info are stored in that ArrayList.
	//CSV file is expected to follow the format 
	//time; Ticker; trade amount; stock price.
	//No other format will be accepted.
	public void csvParse(Scanner in, ArrayList<Trade> trades) {
		while(true) {
			Scanner csvScanner=null;
			String fileName = null;
			File file = null;
			try {
				System.out.println("What is the name of the file containing the schedule information?");
				fileName = in.nextLine();
				file = new File(fileName);
				csvScanner = new Scanner(file);
			}catch(FileNotFoundException fnf) {
				System.out.println("The file "+fileName+" could not be found.");
				continue;
			}
			Scanner helper = null;
			try {
				while (csvScanner.hasNextLine())  
				{  
					helper = new Scanner(csvScanner.nextLine());
					helper.useDelimiter(",");  
					int time = Integer.parseInt(helper.next());
					String company = new String(helper.next());
					int amount =Integer.parseInt(helper.next());
					int price = Integer.parseInt(helper.next());
					trades.add(new Trade(time, company,amount,price));
				}   
			}catch(NumberFormatException nfe) {
				System.out.println("The file is not formatted properlly");
				csvScanner.close();
				helper.close();
				continue;
			}
			csvScanner.close();
			helper.close();
			System.out.println("The file has been proferlly read");
			return;
		}
	}
	//Gets the initial amount of balance.
	//Only accept positive integer number.
	//Negative integer or letters will not be accepted.
	public int getAmount(Scanner in) {
		while(true) {
			System.out.println("What is the Initial Balance?");
			String ans = in.nextLine();
			int amount;
			try {
				amount = Integer.parseInt(ans);
				if(amount<0) {
					throw new NumberFormatException();
				}
				return amount;
			}catch(NumberFormatException nfe){
				System.out.println("Wrong number");
			}
		}
	}
}
