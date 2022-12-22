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
			localStorage.setItem("username",document.getElementById("username-login").value);
			location.href='userhome.html';
		}
		
		
	
	}
	x1http.open("GET", "http://localhost:9090/yitianhu_CSCI201_Assignment4/login?username="+
					(document.getElementById("username-login").value)+"&password="+
					(document.getElementById("password-login").value), true);
 	x1http.send();
}

function f3(){
	var pas = document.getElementById("password").value;
	var pascon = document.getElementById("password-conf").value;
	if(pas!=pascon){
		alert("Mismatch of password!");
	}
	else{
		var x1http = new XMLHttpRequest();
		x1http.onload = function() {
			var res=JSON.parse(this.responseText);
			if(res.result==="true"){
				localStorage.setItem("username",document.getElementById("username").value);
				location.href='userhome.html';
			}
			else if(res.result==="nope"){
				alert("Email is already been taken");
			}
			else if(res.result==="no"){
				alert("Username is already been taken");
			}
			else{
				alert(res.result);
			}
		}
		x1http.open("GET", "http://localhost:9090/yitianhu_CSCI201_Assignment4/signup?username="+
						(document.getElementById("username").value)+"&password="+
						(document.getElementById("password").value)+"&email="+
						(document.getElementById("email").value), true);
	 	x1http.send();
	}
	
};