package yitianhu_CSCI201_Assignment4;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/signup")
public class Signup extends HttpServlet{
	private static final long serialVersionUID = 1L;
	public Signup() {
		super();
	}
	protected void service(HttpServletRequest request, HttpServletResponse response) throws IOException{
		response.setContentType("application/json");
		String username=request.getParameter("username");
		String password=request.getParameter("password");
		String email = request.getParameter("email");
		PrintWriter out = response.getWriter();
		String result = connector.signup(email,username, password);

		out.println(result);
		out.flush();
		
	}

}
