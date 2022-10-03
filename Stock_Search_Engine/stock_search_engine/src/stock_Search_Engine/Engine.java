package stock_Search_Engine;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;
import org.apache.commons.text.WordUtils;
import java.io.File;
import com.google.gson.Gson ;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonParseException;



public class Engine {
	private String data = "";
	private Gson gson;
	private Content content;
	private String fileName;
	
	public Engine()
	{
		gson = new GsonBuilder()
				.setPrettyPrinting()
				.disableHtmlEscaping()
		        .create(); 
				
	}
	//Open a JSON file in designated format
	//and parse the content
	public void openFile(Scanner in)
	{
		while(true)
		{
			data = "";
			try {
				System.out.println("What is the name of the company file?");
				fileName = in.nextLine();
				File file = new File(fileName);
				Scanner sc = new Scanner(file);
				while(sc.hasNext())
				{
					data+=sc.nextLine();
				}
				content = gson.fromJson(data, Content.class);
				if(content==null) {
					sc.close();
					throw new JsonParseException("Empty file");
				}
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
				}
				System.out.println("The file has been properly read.");
				sc.close();
				break;
				
			}catch(FileNotFoundException fnf){
				System.out.println("The file "+fileName+" could not be found.");
			}catch(JsonParseException jpe){
				System.out.println("The file "+fileName+" is not formatted properly.");
				System.out.println(jpe.getMessage());
			}
		}
	}
	
	
	public void openInterface(Scanner in)
	{
		String cmd = "";
		while(true)
		{
			System.out.println("\n"+"          1) Display all public companies");
			System.out.println("          2) Search for a stock (by ticker)");
			System.out.println("          3) Search for all stocks on an exchange");
			System.out.println("          4) Add a new company/stocks");
			System.out.println("          5) Remove a company");
			System.out.println("          6) Sort companies");
			System.out.println("          7) Exit");
			System.out.println("What would you like to do?"+"\n");
			
			try {
				cmd = in.nextLine();
				int userCommand = Integer.parseInt(cmd);
				if(userCommand<1||userCommand>7) {
					throw new NumberFormatException();
				}
				if(userCommand==7) {
					this.cmd7(in);
					return;
				}
				else if(userCommand==1) {
					this.cmd1();
				}
				else if(userCommand==2) {
					this.cmd2(in);
				}
				else if(userCommand==3) {
					this.cmd3(in);
				}
				else if(userCommand==4) {
					this.cmd4(in);
				}
				else if(userCommand==5) {
					this.cmd5(in);
				}
				else if(userCommand==6) {
					this.cmd6(in);
				}
					
			}catch(NumberFormatException ime) {
				System.out.println("That is not a valid option."+"\n");
			}
			
		}
		
	}
	
	//Display all the companies and their info
	public void cmd1() {
		if(content.getData().isEmpty()) {
			System.out.println("There's no company left. Nothing to display.");
			return;
		}
		for(int i=0; i< content.getData().size(); i++) {
			String temp1 = content.getDataByIndex(i).getName();
			temp1 = temp1 + ", symbol "+ content.getDataByIndex(i).getTicker()+", started on ";
			temp1 = temp1 + content.getDataByIndex(i).getStartDate()+", listed on ";
			temp1 = temp1 + content.getDataByIndex(i).getExchangeCode()+",";
			String temp2 = "\t"+content.getDataByIndex(i).getDescription();
			System.out.println(temp1);
			System.out.println(WordUtils.wrap(temp2, 70, "\n\t", true));
		}
		
	}
	//Search a stock by its ticker
	public void cmd2(Scanner in) {
		if(content.getData().isEmpty()) {
			System.out.println("There's no company left. Nothing to be searched for.");
			return;
		}
		String ticker = "";
		while(true) {
			System.out.println("What is the ticker of the company you would like to search for?");
			ticker = in.nextLine();
			for(int i=0; i< content.getData().size(); i++) {
				String temp = content.getDataByIndex(i).getTicker();
				if(temp.toLowerCase().equals(ticker.toLowerCase())) {
					String temp1 = content.getDataByIndex(i).getName();
					temp1 = temp1 + ", symbol "+ content.getDataByIndex(i).getTicker()+", started on ";
					temp1 = temp1 + content.getDataByIndex(i).getStartDate()+", listed on ";
					temp1 = temp1 + content.getDataByIndex(i).getExchangeCode();
					System.out.println(temp1);
					return;
				}
			}
			System.out.println(ticker+ " could not be found.");
		}
	}
	//Search for all the stocks on an exchange.
	public void cmd3(Scanner in) {
		String stockExchange = "";
		List<String> output = new ArrayList<String>();
		boolean found = false;
		while(found ==false) {
			System.out.println("What Stock Exchange would you like to search for?");
			stockExchange = in.nextLine();
			if(!stockExchange.toLowerCase().equals("nasdaq")&&!stockExchange.toLowerCase().equals("nyse")) {
				System.out.println("No exchange named "+stockExchange.toUpperCase()+" found.");
				continue;
			}
			for(int i=0; i< content.getData().size(); i++) {
				String temp = content.getDataByIndex(i).getExchangeCode();
				if(temp.toLowerCase().equals(stockExchange.toLowerCase())) {
					found=true;
					output.add(content.getDataByIndex(i).getTicker());
				}
			}
			if(found==true) {
				System.out.print(output.get(0));
				for(int i=1; i<output.size(); i++) {
					System.out.print(" and "+output.get(i));
				}
				System.out.print(" found on the "+stockExchange.toUpperCase()+" exchange.\n");
				return;
			}
			else {
				System.out.println("No company found on the "+stockExchange.toUpperCase()+" exchange.\n");
				return;
			}
		}
	}
	//Add new stocks
	public void cmd4(Scanner in) {
		String name ;
		String temp ;
		Datum newEntry = new Datum();
		
		//Get Company Name.
		while(true) {	
			System.out.println("What is the name of the company you would like to add?");
			name =in.nextLine();
			if(name.isBlank()) {
				System.out.println("Name can't be empty.");
				continue;
			}
			try {
				for(int i=0; i< content.getData().size(); i++) {
					temp = content.getDataByIndex(i).getName();
					if(temp.toLowerCase().equals(name.toLowerCase())) {
						throw new IllegalArgumentException("There is already an entry for "+name+".");
					}
				}
				newEntry.setName(name);
				break;
			}catch(IllegalArgumentException iae){
				System.out.println(iae.getMessage());
			}
		}
		//Get Ticker
		while(true) {
			System.out.println("What is the stock symbol of "+ newEntry.getName()+ "?");
			name = in.nextLine();
			if(name.isBlank()) {
				System.out.println("Stock symbol can't be empty.");
				continue;
			}
			try {
				for(int i=0; i< content.getData().size(); i++) {
					temp= content.getDataByIndex(i).getTicker();
					if(temp.toLowerCase().equals(name.toLowerCase())) {
						throw new IllegalArgumentException("There is already an entry for ticker "+name+"." );
					}
				}
				newEntry.setTicker(name.toUpperCase());
				break;
			}catch(IllegalArgumentException iae) {
				System.out.println(iae.getMessage());
			}
		}
		//Get Date
		while(true) {
			System.out.println("What is the start date of "+ newEntry.getName()+ "?");
			name = in.nextLine();
			try {
				String [] date= name.split("-");
				if(date.length!=3) {
					throw new NumberFormatException("Wrong date format.");
				}
				else if(Integer.parseInt(date[0])<0) {
					throw new NumberFormatException("Wrong year.");
				}
				else if(Integer.parseInt(date[1])>12||Integer.parseInt(date[1])<1) {
					throw new NumberFormatException("Wrong month.");
				}
				else if(Integer.parseInt(date[2])>31||Integer.parseInt(date[2])<1) {
					throw new NumberFormatException("Wrong day.");
				}
				newEntry.setStartDate(name);
				break;
			}catch(NumberFormatException nfe) {
				System.out.println("This is an invalid date. "+nfe.getMessage());
			}catch(IllegalArgumentException iae) {
				System.out.println("This is an invalid date "+iae.getMessage()+".");
			}
		}
		
		while(true) {
			System.out.println("What is the exchange where "+newEntry.getName() +" is listed?");
			name=in.nextLine();
			if(!name.toUpperCase().equals("NASDAQ")&&!name.toUpperCase().equals("NYSE")) {
				System.out.println("This is not a valid exchange code");
				continue;
			}
			newEntry.setExchangeCode(name.toUpperCase());
			break;
		}
		
		System.out.println("What is the description of "+newEntry.getName()+"?");
		name=in.nextLine();
		newEntry.setDescription(name);
		
		content.getData().add(newEntry);
		
		System.out.println("There is now a new entry for:");
		temp = newEntry.getName();
		temp = temp + ", symbol "+ newEntry.getTicker()+", started on ";
		temp = temp + newEntry.getStartDate()+", listed on ";
		temp = temp + newEntry.getExchangeCode()+",";
		String temp1 = "\t"+newEntry.getDescription();
		System.out.println(temp);
		System.out.println(WordUtils.wrap(temp1, 70, "\n\t", true));
	}
	
	//Delete a stock
	public void cmd5(Scanner in) {
		if(content.getData().isEmpty()) {
			System.out.println("There's no company left. Nothing to remove.");
			return;
		}
		String name;
		while(true) {
			try {
				for(int i=0; i< content.getData().size(); i++) {
					System.out.println("          "+(i+1)+") "+content.getDataByIndex(i).getName());
				}
				System.out.println("Which company would you like to remove?");
				name = in.nextLine();
				int command = Integer.parseInt(name);
				if(command<1||command>content.getData().size()) {
					throw new NumberFormatException();
				}
				else {
					System.out.println(content.getDataByIndex(command-1).getName()+" is now removed.");
					content.getData().remove(command-1);
					return;
				}
			}catch(NumberFormatException nfe) {
				System.out.println("That is not a valid option.");
			}
		}
		
	}
	
	//Sort the stocks by their name.
	public void cmd6(Scanner in) {
		if(content.getData().isEmpty()) {
			System.out.println("There's no company left. Nothing to be sorted.");
			return;
		}
		String name;
		int command;
		while(true) {
			try {
				System.out.println("          1) A to Z");
				System.out.println("          2) Z to A");
				System.out.println("How would you like to sort by?");
				name = in.nextLine();
				command=Integer.parseInt(name);
				if(command<1||command>2) {
					throw new NumberFormatException();
				}
				else if(command ==1) {
					Collections.sort(this.content.getData());
					return;
				}
				else if(command ==2) {
					Collections.sort(this.content.getData(),Collections.reverseOrder());
					return;
				}
			}catch(NumberFormatException nfe) {
				System.out.println("That is not a valid option.");
			}
		}
	}
	
	//Prompt the user to store the changes and exit the interface.
	public void cmd7(Scanner in) {
		FileWriter fw = null;
		PrintWriter pw = null;
		while(true) {
			try {
				System.out.println("          1) Yes");
				System.out.println("          2) No");
				System.out.println("Would you like to save your edits?");
				int cmd = Integer.parseInt(in.nextLine());
				if(cmd<1||cmd>2) {
					throw new NumberFormatException();
				}
				else if(cmd==1) {
					fw = new FileWriter(fileName);
					pw = new PrintWriter(fw);
					pw.print(gson.toJson(content));
					pw.flush();
					fw.close();
					pw.close();
					System.out.println("Your edits have been saved to "+this.fileName);
				}
				else if(cmd==2) {
					System.out.println("Your edits are not saved to "+this.fileName);
				}
				System.out.println("Thank you for using my program!");
				return;
			}catch(NumberFormatException nfe) {
				System.out.println("That is not a valid option.");
			}catch(IOException ioe) {
				System.out.println(ioe.getMessage());
			}
		}
	}
}

