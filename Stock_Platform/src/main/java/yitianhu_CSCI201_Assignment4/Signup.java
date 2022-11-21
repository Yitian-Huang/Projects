package yitianhu_CSCI201_Assignment4;

import java.io.IOException;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/signup")
public class Signup {
	private static final long serialVersionUID = 1L;
	public Signup() {
		super();
		System.out.println("in constructor");
	}
	protected void service(HttpServletRequest request, HttpServletResponse response) throws IOException{
		
	}

}
