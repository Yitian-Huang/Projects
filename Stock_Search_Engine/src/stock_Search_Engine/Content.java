
package stock_Search_Engine;
import java.util.List;


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