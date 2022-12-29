
// Get the modal
var modal = document.getElementById('idloginModal');

// When the user clicks anywhere outside of the modal, close it
window.onclick = function(event) {
    if (event.target == modal) {
        modal.style.display = "none";
    }
}

const api_url = "http://localhost/api/v1/"; 
var token_ ;
var request = new XMLHttpRequest(); 

function doLogout(){
    document.getElementById('idBtnLogin').style.display='block';
    document.getElementById('idBtnLogout').style.display='none';
    token_ = null;
}

function getToken() {
	const data = new FormData(document.getElementById("formLogin"));
	const value = Object.fromEntries(data.entries());
    request.open("POST", api_url + "auth/login", true); 
    request.setRequestHeader("Content-type", "application/json");
    request.send(JSON.stringify(value));
    request.onreadystatechange = function () {
        if (request.readyState == request.DONE) {
            var response = request.responseText;
            var obj = JSON.parse(response); 
            token_ = obj.token;
        	modal.style.display = "none";

            document.getElementById("idBtnLogin").style.display = "none";
            document.getElementById("idBtnLogout").style.display = "block";
        }
    }
}

function callWebAPI(url) {
    var request = new XMLHttpRequest();        
    request.open("GET", url, true);
    request.setRequestHeader("Authorization", "Bearer "+ token_);
    request.send();
    request.onreadystatechange = function () {
        if (request.readyState == request.DONE && request.status == 200) {
            var response = request.responseText;
            var obj = JSON.parse(response); 
            document.getElementById("idview").innerHTML = response;
        }
        else if (request.readyState == request.DONE && request.status != 200){
            alert(request.status);
        }
    }
} 