package yitianhu_CSCI201_Assignment4;

import java.sql.*;

public class connector {
	public static String login(String name, String password)  {
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = DriverManager.getConnection("jdbc:mysql://localhost/assignment4?user=root&password=root");
			st = conn.createStatement();
			rs = st.executeQuery("SELECT * from user where username='" + name + "'");
			if(!rs.isBeforeFirst()) {
				return "false";
			}
			else {
				rs.next();
				if(rs.getString("password").equals(password)) {
					return "true";
				}
				else {
					return "false";
				}
			}
			
			
		}catch(SQLException sqle) {
			System.out.println ("connector exception"+sqle.getMessage());
			
		}
		return "false";

	}

}
