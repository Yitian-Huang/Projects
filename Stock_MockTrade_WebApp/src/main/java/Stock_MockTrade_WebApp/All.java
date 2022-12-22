package Stock_MockTrade_WebApp;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/all")
public class All extends HttpServlet{
	private static final long serialVersionUID = 1L;
	public All() {
		super();
	}
	protected void service(HttpServletRequest request, HttpServletResponse response) throws IOException{
		response.setContentType("application/json");
		String username=request.getParameter("username");
		PrintWriter out = response.getWriter();
		String result = connector.getAll(username);
		out.println(result);
		out.flush();
	}
	

}