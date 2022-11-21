/**
 * 
 */
 function f1(){
	var x1http = new XMLHttpRequest();
	x1http.onload = function() {
		var res=JSON.parse(this.responseText);
		if(JSON.stringify(res)==="false"){
			alert("Incorrect Username or Password");
		}
		else{
			location.href='home.html';
		}
		
		
	
	}
	x1http.open("GET", "http://localhost:9090/yitianhu_CSCI201_Assignment4/login?username="+
					(document.getElementById("username-login").value)+"&password="+
					(document.getElementById("password-login").value), true);
 	x1http.send();
}
