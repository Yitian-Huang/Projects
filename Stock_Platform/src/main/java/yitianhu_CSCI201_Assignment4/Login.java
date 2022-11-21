package yitianhu_CSCI201_Assignment4;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.*;
import java.util.List;

@WebServlet("/login")
public class Login extends HttpServlet{
	private static final long serialVersionUID = 1L;
	public Login() {
		super();
		System.out.println("in constructor");
	}
	protected void service(HttpServletRequest request, HttpServletResponse response) throws IOException{
		response.setContentType("application/json");
		String username=request.getParameter("username");
		String password=request.getParameter("password");
		PrintWriter out = response.getWriter();
		String result = connector.login(username, password);
		out.println(result);
	}

}

