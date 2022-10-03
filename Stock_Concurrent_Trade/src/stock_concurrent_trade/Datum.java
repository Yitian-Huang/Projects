package stock_concurrent_trade;
//Data class that stores all the info of a single company in the JSON file
//Getters/Setters are implemented and this class allows sorting by company name
//JSON file needs to provide necessary info about each company.
public class Datum implements Comparable<Datum>{

	private String name;
	private String ticker;
	private String startDate;
	private int stockBrokers =-100;
	private String description;
	private String exchangeCode;

	public Datum() {}
	
	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}
	
	public String getTicker() {
		return ticker;
	}
	
	public void setTicker(String ticker) {
		this.ticker = ticker;
	}
	
	public String getStartDate() {
		return startDate;
	}
	
	public void setStartDate(String startDate) {
		this.startDate = startDate;
	}
	
	public int getStockBrokers() {
		return stockBrokers;
	}

	public void setStockBrokers(int stockBroker) {
		this.stockBrokers = stockBroker;
	}
	
	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}
	
	public String getExchangeCode() {
		return exchangeCode;
	}
	
	public void setExchangeCode(String exchangeCode) {
		this.exchangeCode = exchangeCode;
	}
	
	//Found from https://howtodoinjava.com/java/sort/collections-sort/
	public int compareTo(Datum d) {
		return (this.getName().compareToIgnoreCase(d.getName()));
	}
	
}