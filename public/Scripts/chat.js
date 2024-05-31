let data = {
    "msg": "",
    "state": "null"
};

let send = async function() {
    const msg = document.getElementById("msgBox").value;
    
    let currentData = await fetch(`/api/send?msg=${msg}`, {
        method: "GET"
    });

    currentData = await currentData.text();
    console.log(currentData);
}

let start = async function() {
    let currentData = await fetch("/api/chat.json", {
        method: "GET"
    });

    currentData = await currentData.json();
    let message = currentData.msg;

    data.msg = message;
    data.state = currentData.state;

    const messageHTML = document.createElement('li');
    messageHTML.innerText = message.replace(/%20/g, " ");
    document.querySelector('ul').append(messageHTML);
}

let update = async function() {
    let currentData = await fetch("/api/chat.json", {
        method: "GET"
    });
    currentData = await currentData.json();
    let message = await currentData.msg;

    if(data.state == currentData.state) { return; }

    data.msg = message;
    data.state = currentData.state;

    const messageHTML = document.createElement('li');
    document.querySelector('ul').append(decodeURIComponent(messageHTML));
}

start();
setInterval(update, 100); // Updates chat 10 times a second
