package stock_concurrent_trade;

import java.util.List;

//Data class that stores all the companies in the JSON file
//in an ArrayList. Getters/Setters are implemented
public class Content {
	public Content() {}

	private List<Datum> data = null;

	public List<Datum> getData() {
		return data;
	}
	
	public Datum getDataByIndex(int idx) {
		return data.get(idx);
	}
	
	public void setData(List<Datum> data) {
		this.data = data;
	}

}
