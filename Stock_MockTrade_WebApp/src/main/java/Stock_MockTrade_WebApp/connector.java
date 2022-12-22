package Stock_MockTrade_WebApp;

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
	public static String signup(String email, String username, String password) {
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = DriverManager.getConnection("jdbc:mysql://localhost/assignment4?user=root&password=root");
			st = conn.createStatement();
			rs = st.executeQuery("SELECT * from user where username='" + username + "'");
			if(rs.isBeforeFirst()) {
				return "{\"result\":\"no\"}";
			}
			else {
				rs = st.executeQuery("SELECT * from user where email='" + email + "'");
				if(rs.isBeforeFirst()) {
					return "{\"result\":\"nope\"}";
				}
				else {
					st.executeUpdate("insert into user(username,email,password,money) values("+
										"\""+username+"\""+","+"\""+email+"\""+","+"\""+password+"\""+","+50000+")");
					String sql = "CREATE TABLE " +username+
			                   "(ticker varchar(255) not null, " +
			                   " amount int(10) not null, " + 
			                   " cost Double not null );";
					st.executeUpdate(sql);
					return "{\"result\":\"true\"}";
				}
				
			}
			
			
		}catch(SQLException sqle) {
			System.out.println ("connector exception"+sqle.getMessage());
			
		}
		return "{\"result\":\"false\"}";
	}
	
	public static String setAmount(String username,int amount, Double prc,String ticker) {
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = DriverManager.getConnection("jdbc:mysql://localhost/assignment4?user=root&password=root");
			st = conn.createStatement();
			rs = st.executeQuery("SELECT money from user where username='" + username + "'");
			rs.next();
			if( rs.getDouble("money")>=prc) {
				String sqlUpdate = "UPDATE user "
		                + "SET money = "+(rs.getDouble("money")-prc)
		                + "WHERE username = "+"\""+username+"\"";
				st.executeUpdate(sqlUpdate);
				rs=st.executeQuery("SELECT * from "+username+" where ticker='" + ticker + "'");
				if(!rs.isBeforeFirst()) {
					String ud="insert into "+username+"(ticker,amount,cost) values("+
								"\""+ticker+"\", "+"\""+amount+"\","+"\""+prc+"\")";
					st.executeUpdate(ud);
				}
				else {
					rs.next();
					Integer amo = (Integer) rs.getObject("amount");
					if((amo+amount)==0) {
						String ud="delete from "+username+" where ticker = "+"\""+ticker+"\"";
						st.executeUpdate(ud);
						
					}
					else {
						Double pr = rs.getDouble("cost");
						String ud="update "+username+" set amount = "+(amo+amount) +" where ticker = "+"\""+ticker+"\"";
						st.executeUpdate(ud);
						ud="update "+username+" set cost = "+(pr+prc) +" where ticker = "+"\""+ticker+"\"";
						st.executeUpdate(ud);
					}
					
				}
				return "{\"result\":\"true\"}";
			}
		}catch(SQLException sqle) {
			System.out.println ("connector exception"+sqle.getMessage());
		}
		return"{\"result\":\"false\"}";
	}
	
	public static Double getAmount(String username) {
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			conn = DriverManager.getConnection("jdbc:mysql://localhost/assignment4?user=root&password=root");
			st = conn.createStatement();
			rs=st.executeQuery("SELECT money from user where username='" + username + "'");
			rs.next();
			return rs.getDouble("money");
		}
		catch(SQLException sqle) {
			System.out.println ("connector exception"+sqle.getMessage());
		}
		return 0.0;
	}

	public static String getAll(String username) {
		Connection conn = null;
		Statement st = null;
		ResultSet rs = null;
		String retval="[";
		try {
			conn = DriverManager.getConnection("jdbc:mysql://localhost/assignment4?user=root&password=root");
			st = conn.createStatement();
			rs=st.executeQuery("SELECT * from "+ username);
			rs.next();
			retval+=" { \"ticker\" : "+"\""+rs.getString("ticker")+"\",";
			retval+="\"quantity\" : "+(Integer)rs.getObject("amount")+", ";
			retval+="\"cost\" : "+rs.getDouble("cost")+"} ";
			while(rs.next()) {
				retval+=", { \"ticker\" : "+"\""+rs.getString("ticker")+"\",";
				retval+="\"quantity\" : "+(Integer)rs.getObject("amount")+", ";
				retval+="\"cost\" : "+rs.getDouble("cost")+"}";
			}
			retval+="]";
			return retval;
		}catch(SQLException sqle) {
			System.out.println ("connector exception"+sqle.getMessage());
		}
		return "";
	}

}
