package yitianhu_CSCI201_Assignment4;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/transact")

public class Transact extends HttpServlet{
	private static final long serialVersionUID = 1L;
	public Transact() {
		super();
	}
	protected void service(HttpServletRequest request, HttpServletResponse response) throws IOException{
		response.setContentType("application/json");
		String username=request.getParameter("username");
		String Buy = request.getParameter("buy");
		int amount = Integer.parseInt(request.getParameter("amount"));
		PrintWriter out = response.getWriter();
		String result = connector.getAll(username);
		out.println(result);
		out.flush();
	}
	

}
