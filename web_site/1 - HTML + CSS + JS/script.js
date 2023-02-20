// JavaScript
document.getElementById("welcome").innerText += 
" sam_sam_237";

document.getElementById("button").addEventListener ("click", fun);

function fun() {  
	if (document.getElementById('your_name').value != ""){
		document.getElementById("result").innerHTML = "Thanks " +  document.getElementById('your_name').value + "<br>";
		if (document.getElementById('about').value != ""){ document.getElementById("result").innerHTML +="About You : " + document.getElementById('about').value;}
	
	}
	else{ document.getElementById("result").innerHTML = "Thanks ";}
} 
