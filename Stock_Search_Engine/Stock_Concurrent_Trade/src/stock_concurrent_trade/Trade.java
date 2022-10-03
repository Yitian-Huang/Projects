package stock_concurrent_trade;
//Class that stores all the trade info for each single trade.
//ArrayList of all the trades is implemented in the main function.
//Getters are implemented. Changing trade info is not expected and no Setter is provided.
public class Trade {
	private int time;
	private String company;
	private int amount;
	private int price;
	public Trade(int t, String c, int a, int p) {
		time =t;
		company = new String(c);
		amount =a;
		price = p;
	}
	public int getTime() {
		return time;
	}
	public int getAmount() {
		return amount;
	}
	public String getCompany() {
		return company;
	}
	public int getPrice() {
		return price;
	}
}
