
package stock_Search_Engine;


public class Datum implements Comparable<Datum>{

	private String name;
	private String ticker;
	private String startDate;
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
	
	public int compareTo(Datum d) {
		return (this.getName().compareToIgnoreCase(d.getName()));
	}
	
}