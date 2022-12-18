package yitianhu_CSCI201_Assignment4;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/buy")
public class Buy extends HttpServlet{
	private static final long serialVersionUID = 1L;
	public Buy() {
		super();
	}
	protected void service(HttpServletRequest request, HttpServletResponse response) throws IOException{
		response.setContentType("application/json");
		String username=request.getParameter("username");
		String ticker = request.getParameter("ticker");
		int amount = Integer.parseInt(request.getParameter("amount"));
		Double prc = Double.parseDouble(request.getParameter("prc"));
		PrintWriter out = response.getWriter();
		String result = connector.setAmount(username,amount,prc,ticker);
		out.println(result);
		out.flush();
	}
}
