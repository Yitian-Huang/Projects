package yitianhu_CSCI201_Assignment4;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/amount")
public class Amount extends HttpServlet{
	private static final long serialVersionUID = 1L;
	public Amount() {
		super();
	}
	protected void service(HttpServletRequest request, HttpServletResponse response) throws IOException{
		response.setContentType("application/json");
		String username=request.getParameter("username");
		PrintWriter out = response.getWriter();
		Double result = connector.getAmount(username);
		out.println(result);
		out.flush();
	}
	

}
