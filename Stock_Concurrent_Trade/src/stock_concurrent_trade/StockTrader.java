package stock_concurrent_trade;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;
import java.util.TimeZone;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Semaphore;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.List;
 

public class StockTrader {
	private static List<Integer> balance = Collections.synchronizedList(new ArrayList<Integer>());
	
	public static void main(String[] args) {
		//Time stamp format from https://www.geeksforgeeks.org/program-to-convert-milliseconds-to-a-date-format-in-java/
        DateFormat simple = new SimpleDateFormat("HH:mm:ss:SSS");
        simple.setTimeZone(TimeZone.getTimeZone("UTC"));

		Scanner sc = new Scanner(System.in);
		Parser parser = new Parser();
		ArrayList<Trade> trades = new ArrayList<Trade>();
		Content content = null;
		
		Gson gson=new GsonBuilder()
		.setPrettyPrinting()
		.disableHtmlEscaping()
        .create();
		
		content = parser.jsonParse(sc,  gson);
		parser.csvParse(sc, trades);
		StockTrader.balance.add(parser.getAmount(sc));
		//Initialize semaphore
		TraderThread.sems = new ArrayList<Semaphore>();
		for(int i=0; i<content.getData().size(); i++) {
			TraderThread.sems.add(new Semaphore(content.getData().get(i).getStockBrokers()));
		}
		
		System.out.println("Initial Balance: "+StockTrader.balance.get(0));
		
		long startTime = System.currentTimeMillis();
		ExecutorService executor = Executors.newCachedThreadPool();
		int currentTime=0;
		
		//Execute all the trades.
		for(int i=0; i<trades.size(); i++) {
			try {
				Thread.sleep(1000*(trades.get(i).getTime()-currentTime));
				currentTime = trades.get(i).getTime();
			}catch(InterruptedException ie){
				System.out.println(ie.getMessage());
			}catch(IllegalArgumentException iae) {
				System.out.println("Wrong transcation time of "+trades.get(i).getCompany());
				continue;
			}
			int idx =0;
			for(int j=0; j<content.getData().size(); j++) {
				if(content.getData().get(j).getTicker().equals(trades.get(i).getCompany())) {
					idx = j;
				}
			}
			executor.execute(new TraderThread(trades.get(i), startTime, simple, idx));
			currentTime =trades.get(i).getTime();
		}
		executor.shutdown();
		while(!executor.isTerminated()) {
			Thread.yield();
		}
		System.out.println("All trades completed!");
	}
	
	public void addBalance(int amount){	
		balance.set(0,balance.get(0)+amount);
	}
	
	public int getBalance() {
		return balance.get(0);
	}
	

}
