package stock_concurrent_trade;

import java.text.DateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

//Thread class that is responsible for each single trade.
public class TraderThread extends Thread{
	//An ArrayList of semaphores. Each semaphore object in the array
	//represents the number of stock brokers for that company.
	public static ArrayList<Semaphore> sems;
	private static StockTrader st = new StockTrader();
	private static Lock lock = new ReentrantLock();
	private Trade trade = null;
	private int idx;
	private long sTime;
	private DateFormat simple;
	public TraderThread (Trade t,long time, DateFormat s, int i) {
		trade =t;
		sTime = time;
		simple = s;
		idx =i;
	}
	
	public void run() {
		try {
			//First acquire permit from semaphore
			//If all the stock brokers for that company are 
			//currently dealing with a trade, this trade will 
			//wait until a stock broker is available.
			sems.get(idx).acquire();
			//Stock Purchase
			if(trade.getAmount()>0) {
				System.out.println("["+simple.format(new Date(System.currentTimeMillis()-sTime))+"]"
				+"Starting purchase of "+ trade.getAmount()+" stocks of "+trade.getCompany());
				
				if(trade.getAmount()*trade.getPrice()>st.getBalance()) {
					lock.lock();
					System.out.println("Transaction failed due to insufficient balance. "
					+ "Unsuccessful purchase of "+ trade.getAmount()+" stocks of "+trade.getCompany());
				}
				
				else {
					Thread.sleep(2000);
					lock.lock();
					st.addBalance(-trade.getAmount()*trade.getPrice());
					System.out.println("["+simple.format(new Date(System.currentTimeMillis()-sTime))+"]"
					+"Finished purchase of "+ trade.getAmount()+" stocks of "+trade.getCompany()
					+"\nCurrent balance after trade: "+st.getBalance());
				}
			}
			//Stock sale
			else {
				System.out.println("["+simple.format(new Date(System.currentTimeMillis()-sTime))+"]"
				+"Starting sale of "+ (-trade.getAmount())+" stocks of "+trade.getCompany());
				Thread.sleep(3000);
				lock.lock();
				st.addBalance(-trade.getAmount()*trade.getPrice());
				System.out.println("["+simple.format(new Date(System.currentTimeMillis()-sTime))+"]"
				+"Finished sale of "+ (-trade.getAmount())+" stocks of "+trade.getCompany()
				+"\nCurrent balance after trade: "+st.getBalance());
			}
			
		}catch(InterruptedException ie) {
			System.out.println(ie.getMessage());
		}catch(IllegalArgumentException iae){
			System.out.println("Wrong transcation time");
		}finally {
			sems.get(idx).release();
			lock.unlock();
		}
		
	}

	
}
