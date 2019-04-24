// // https://github.com/sindresorhus/sdbm
// const sdbm = string => {
// 	let hash = 0;

// 	for (let i = 0; i < string.length; i++) {
// 		hash = string.charCodeAt(i) + (hash << 6) + (hash << 16) - hash;
// 	}

// 	// Convert it to an unsigned 32-bit integer
// 	return hash >>> 0;
// };

// https://stackoverflow.com/a/7220510
// function syntaxHighlight(json) {
//     if (typeof json != 'string') {
//          json = JSON.stringify(json, undefined, 2);
//     }
//     json = json.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
//     return json.replace(/("(\\u[a-zA-Z0-9]{4}|\\[^u]|[^\\"])*"(\s*:)?|\b(true|false|null)\b|-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?)/g, function (match) {
//         var cls = 'number';
//         if (/^"/.test(match)) {
//             if (/:$/.test(match)) {
//                 cls = 'key';
//             } else {
//                 cls = 'string';
//             }
//         } else if (/true|false/.test(match)) {
//             cls = 'boolean';
//         } else if (/null/.test(match)) {
//             cls = 'null';
//         }
//         return '<span class="' + cls + '">' + match + '</span>';
//     });
// }


// https://stackoverflow.com/questions/36631762/returning-html-with-fetch
// https://stackoverflow.com/a/50812705
// https://www.codecademy.com/articles/what-is-cors

// http://[fd00::212:4b00:f24:8385]/

console.log('hello world');


///////////////////////////////////////////////////////////////////////////////
// FUNCTIONS //////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

function oarCrypt(input, key) {
    // var key = ['!', '@', '#', '$', '%', '^', '&', '*'];
    var output = [];
    
    for (var i = 0; i < input.length; i++) {
        var charCode = input.charCodeAt(i) ^ (key[i % key.length].charCodeAt(0));
        output.push(String.fromCharCode(charCode));
    }
    return output.join("");
}

// SDBM non-cryptographic hash function
// https://github.com/sindresorhus/sdbm

const sdbm = string => {
	let hash = 0;

	for (let i = 0; i < string.length; i++) {
		hash = string.charCodeAt(i) + (hash << 6) + (hash << 16) - hash;
	}

	// Convert it to an unsigned 32-bit integer
	return hash >>> 0;
};

// generate nodes-input section
// construct GET requests to nodes
// query nodes specifying path

function nodesInputHTML(nodesAddr) {

    let nodesInputHTML = ''

    nodesAddr.forEach((node, index) => {

        nodesInputHTML += `
            <div class="p-2 p-auto m-2 m-auto input-group"> 
                <div class="input-group-prepend"> 
                    <button class="btn btn-primary" type="button" id="nodes-button-${index}">GET</button>  
                </div> 
                <div class="input-group-prepend"> 
                    <span class="input-group-text">http://</span>  
                </div> 
                <input type="text" class="form-control" value='${node}' id="nodes-addr-input-${index}"></input> 
                <div class="input-group-append"> 
                    <span class="input-group-text">/</span> 
                </div>
                    <input type="number" class="form-control"  id="nodes-path-input-${index}"></input> 
            </div>
            <div class="row text-center justify-content-center" id="nodes-output-${index}"></div>`
    })

    nodesInputHTML += `<div class="container" id="nodes-response"></div>`

    return nodesInputHTML;

}


///////////////////////////////////////////////////////////////////////////////
// STATIC HTML ELEMENTS GLOBAL DECLARATIONS ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// BORDER ROUTER

const brDiv = document.getElementById('br-div');
const brButton = document.getElementById('br-button');

const brInput = document.getElementById('br-input');
const brOutput = document.getElementById('br-output');

const neighborsElement = document.getElementById('neighbors');
const routingLinksElement = document.getElementById('routing-links');

const brButtonReload = document.getElementById('br-button-reload');
const brButtonClear = document.getElementById('br-button-clear');
const brButtonContinue = document.getElementById('br-button-continue');

// NODES

const nodesDiv = document.getElementById('nodes-div');
const nodesH1 = document.getElementById('nodes-h1');

const nodesButtonIndex = document.getElementById('nodes-button-index');

const nodesInput = document.getElementById('nodes-input');

const nodesEncodedResponseDiv = document.getElementById('nodes-encoded-response-div');
const nodesButtonDecode = document.getElementById('nodes-button-decode');

const nodesEncryptedResponseDiv = document.getElementById('nodes-encrypted-response-div');
const nodesButtonDecrypt = document.getElementById('nodes-button-decrypt');

const nodesKeySpan = document.getElementById('nodes-key-span');
const nodesKeyInput = document.getElementById('nodes-key-input');

const nodesStringifiedResponseDiv = document.getElementById('nodes-stringified-response-div');

const nodesButtonParse = document.getElementById('nodes-button-parse');
const nodesButtonChecksum = document.getElementById('nodes-button-checksum');

const nodesOutputChecksum = document.getElementById('nodes-output-checksum');
const nodesParsedResponseDiv = document.getElementById('nodes-parsed-response-div');

const nodesButtonReload = document.getElementById('nodes-button-reload');
const nodesButtonClear = document.getElementById('nodes-button-clear');
const nodesButtonContinue = document.getElementById('nodes-button-continue');

// CONSOLE

const consoleDiv = document.getElementById('console-div');
const consoleH1 = document.getElementById('console-h1');

const consoleButtonReload = document.getElementById('console-button-reload');
const consoleButtonClear = document.getElementById('console-button-clear');
const consoleButtonContinue = document.getElementById('console-button-continue');










///////////////////////////////////////////////////////////////////////////////
// RELOAD BUTTONS FUNCTIONALITY ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// BORDER ROUTER

brButtonReload.addEventListener('click', () => {
    event.preventDefault();
    window.location.reload(true);
});

// NODES

nodesButtonReload.addEventListener('click', () => {
    event.preventDefault();
    window.location.reload(true);
});


///////////////////////////////////////////////////////////////////////////////
// CLEAR BUTTONS FUNCTIONALITY ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// BORDER ROUTER

brButtonClear.addEventListener('click', () => {
                        
    brDiv.classList.remove('border-danger', 'border-warning', 'border-success');
    brDiv.classList.add('border-info');
    
    neighborsElement.innerHTML = '';
    routingLinksElement.innerHTML = '';
    
    brOutput.classList.replace('d-block', 'd-none');
    nodesEncodedResponseDiv.innerText = ''
})

// NODES

nodesButtonClear.addEventListener('click', () => {

    nodesDiv.classList.remove('border-danger', 'border-warning', 'border-success');
    nodesDiv.classList.add('border-primary');

    nodesButtonIndex.classList.replace('d-none', 'd-block');

    nodesInput.innerHTML = '';

    nodesEncodedResponseDiv.classList.replace('d-block', 'd-none');
    nodesEncryptedResponseDiv.classList.replace('d-block', 'd-none');
    nodesStringifiedResponseDiv.classList.replace('d-block', 'd-none');
    
    nodesEncodedResponseDiv.classList.replace('text-dark', 'text-light');
    nodesEncodedResponseDiv.innerText = '_';
    nodesEncryptedResponseDiv.classList.replace('text-dark', 'text-light');
    nodesEncryptedResponseDiv.innerText = '_';
    nodesStringifiedResponseDiv.classList.replace('text-dark', 'text-light');
    nodesStringifiedResponseDiv.innerText = '_';

    nodesButtonDecode.classList.replace('d-block', 'd-none');
    nodesButtonDecrypt.classList.replace('d-block', 'd-none');
    nodesButtonChecksum.classList.replace('d-block', 'd-none');
    nodesButtonParse.classList.replace('d-block', 'd-none');
    
    nodesButtonDecode.classList.remove('btn-outline-danger', 'btn-outline-warning', 'btn-outline-success', 'btn-outline-primary', 'btn-outline-secondary');
    nodesButtonDecode.classList.remove('btn-danger', 'btn-warning', 'btn-success', 'btn-primary', 'btn-secondary');
    nodesButtonDecode.classList.add('btn-muted');
    nodesButtonDecrypt.classList.remove('btn-outline-danger', 'btn-outline-warning', 'btn-outline-success', 'btn-outline-primary', 'btn-outline-secondary');
    nodesButtonDecrypt.classList.remove('btn-danger', 'btn-warning', 'btn-success', 'btn-primary', 'btn-secondary');
    nodesButtonDecrypt.classList.add('btn-muted');
    nodesButtonChecksum.classList.remove('btn-outline-danger', 'btn-outline-warning', 'btn-outline-success', 'btn-outline-primary', 'btn-outline-secondary');
    nodesButtonChecksum.classList.remove('btn-danger', 'btn-warning', 'btn-success', 'btn-primary', 'btn-secondary');
    nodesButtonChecksum.classList.add('btn-muted');
    nodesButtonParse.classList.remove('btn-outline-danger', 'btn-outline-warning', 'btn-outline-success', 'btn-outline-primary', 'btn-outline-secondary');
    nodesButtonParse.classList.remove('btn-danger', 'btn-warning', 'btn-success', 'btn-primary', 'btn-secondary');
    nodesButtonParse.classList.add('btn-muted');

    nodesKeySpan.classList.replace('d-block', 'd-none');
    nodesKeyInput.classList.replace('d-block', 'd-none');

    nodesOutputChecksum.classList.replace('d-block', 'd-none');

})



///////////////////////////////////////////////////////////////////////////////
// CONTINUE BUTTONS FUNCTIONALITY /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

brButtonContinue.addEventListener('click', () => nodesDiv.classList.replace('d-none', 'd-block'));
nodesButtonContinue.addEventListener('click', () => consoleDiv.classList.replace('d-none', 'd-block'));













// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
// NODES ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

function constructResponse_OK() {

    nodesDiv.classList.remove('border-danger', 'border-warning', 'border-info'); nodesDiv.classList.add('border-success');

    document.getElementById(`nodes-output-${index}`).innerText = 'OK';
    
    document.getElementById(`nodes-output-${index}`).classList.remove('bg-danger', 'bg-warning', 'bg-info'); document.getElementById(`nodes-output-${index}`).classList.add('bg-success');
    document.getElementById(`nodes-output-${index}`).classList.replace('d-none', 'd-block')
    
    document.getElementById('nodes-h2-encoded-response').classList.replace('d-none', 'd-block')

    nodesEncodedResponseDiv.classList.replace('d-none', 'd-block')
    nodesEncodedResponseDiv.innerText = text;

    
    nodesButtonDecode.classList.replace('d-none', 'd-block')
}

function constructDecoding(text) {

    let decodedResponse = atob(text);
    
    nodesEncodedResponseDiv.classList.replace('text-light', 'text-dark');
    nodesButtonDecode.classList.replace('btn-primary', 'btn-outline-success');

    nodesEncryptedResponseDiv.classList.replace('d-none', 'd-block');
    nodesEncryptedResponseDiv.innerText = decodedResponse;

    return decodedResponse
}

function constructDecryption(decodedResponse) {

    nodesEncryptedResponseDiv.classList.replace('text-light', 'text-dark');
    nodesButtonDecrypt.classList.replace('btn-primary', 'btn-outline-success');

    let decryptedResponse = oarCrypt(decodedResponse, nodesKeyInput.value);
    
    nodesStringifiedResponseDiv.classList.replace('d-none', 'd-block');
    nodesStringifiedResponseDiv.innerText = decryptedResponse;

    return decryptedResponse;
}

function checksum(decryptedResponse) {

    try{
        let obj = JSON.parse(decryptedResponse);
        let payloadHash = obj.hash;
        let goa = obj;
        delete goa.hash;
        goa = JSON.stringify(goa);
        let intact = sdbm(goa.substr(0, goa.length -1) + "," ) == payloadHash ? true : false;
        return intact;
    }
    catch(error) {
        console.log(error);
        let intact = false;
        return intact;
    }

   
}

function constructIntactness() {

    nodesButtonChecksum.classList.replace('btn-primary', 'btn-outline-success');                                                        
    nodesOutputChecksum.innerText = 'INTACT';
    nodesOutputChecksum.classList.remove('bg-danger', 'bg-warning'); nodesOutputChecksum.classList.add('bg-success');
    nodesOutputChecksum.classList.replace('d-none', 'd-block');
}

function constructCorruptness() {

    nodesButtonChecksum.classList.replace('btn-primary', 'btn-outline-warning')                                                    
    nodesOutputChecksum.innerText = 'CORRUPTED';
    nodesOutputChecksum.classList.remove('bg-danger', 'bg-success'); nodesOutputChecksum.classList.add('bg-warning');
    nodesOutputChecksum.classList.replace('d-none', 'd-block')

    nodesDiv.classList.remove('bg-danger', 'bg-success', 'bg-info'); nodesDiv.classList.add('bg-warning');
}

function constructParse_OK(parsedResponse) {

    nodesParsedResponseDiv.classList.replace('d-none', 'd-block');
    nodesParsedResponseDiv.innerHTML = JSON.stringify(parsedResponse, null, 2);

    nodesEncodedResponseDiv.classList.replace('text-dark', 'text-secondary');
    nodesEncodedResponseDiv.classList.replace('bg-secondary', 'bg-dark');
    nodesEncodedResponseDiv.classList.replace('border-dark', 'border-secondary');
    
    nodesEncryptedResponseDiv.classList.replace('text-dark', 'text-secondary');
    nodesEncryptedResponseDiv.classList.replace('bg-secondary', 'bg-dark');
    nodesEncryptedResponseDiv.classList.replace('border-dark', 'border-secondary');

    nodesButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

    nodesButtonDecode.classList.replace('btn-outline-success', 'btn-outline-secondary');
    nodesButtonDecrypt.classList.replace('btn-outline-success', 'btn-outline-secondary');
    nodesButtonChecksum.classList.replace('btn-outline-success', 'btn-outline-secondary');

    nodesButtonParse.classList.replace('btn-primary', 'btn-outline-success');
}

function constructParse_FAIL(error) {
    
    nodesDiv.classList.remove('border-warning', 'border-success', 'border-primary'); nodesDiv.classList.add('border-danger');

    nodesOutputChecksum.innerText = error;

    nodesOutputChecksum.classList.remove('bg-success');
    nodesOutputChecksum.classList.remove('bg-warning');
    nodesOutputChecksum.classList.add('bg-danger');
    nodesOutputChecksum.classList.replace('d-none', 'd-block')

    nodesButtonChecksum.classList.remove('btn-outline-danger', 'btn-outline-warning', 'btn-outline-success', 'btn-outline-primary','btn-outline-muted'); nodesButtonChecksum.classList.add('btn-outline-secondary')
    nodesButtonParse.classList.replace('btn-primary', 'btn-outline-danger');

}





brButton.addEventListener('click', scrap);

// BUTTON RELOAD








function scrap() {
    
    console.log(brInput.value)

    fetch(`http://${brInput.value}/`)
        .then(function(response) {
            // console.log(response);
            return response.text()
        })
            .then(function(text) {
                // Initialize the DOM parser
                var parser = new DOMParser();

                // Parse the text
                var br_doc = parser.parseFromString(text, "text/html");

                const uls = br_doc.querySelectorAll('ul');
                console.log(uls);

                try {

                    neighborsNodeList = uls[0].querySelectorAll('li');
                    neighborsArray = Array.from(neighborsNodeList);

                    routingLinksNodeList = uls[1].querySelectorAll('li');
                    routingLinksArray = Array.from(routingLinksNodeList);
                    
                    console.log(neighborsArray);
                    console.log(routingLinksArray);

                    brDiv.classList.remove('border-info', 'border-warning', 'border-danger'); brDiv.classList.add('border-success');
                
                    brOutput.innerText = 'OK';
                    brOutput.classList.remove('bg-info', 'bg-warning', 'bg-danger'); brOutput.classList.add('bg-success');
                    brOutput.classList.replace('d-none', 'd-block')

                    document.getElementById('br-h2-neighbors').classList.replace('d-none', 'd-block')
                    document.getElementById('br-h2-routing-links').classList.replace('d-none', 'd-block')
                    
                    

                    neighborsElement.classList.replace('d-none', 'd-block');
                    routingLinksElement.classList.replace('d-none', 'd-block');

                    let neighborsListHTML = '';
                    let routingLinksListHTML = '';

                    neighborsArray.forEach((neighbor, index) => neighborsListHTML += `<li class="list-group-item text-center bg-dark text-light border-secondary rounded"> ${neighbor.innerText} </li>`);
                    neighborsElement.innerHTML = neighborsListHTML;

                    routingLinksArray.forEach((routingLink, index) => routingLinksListHTML += `<li class="list-group-item text-center bg-dark text-light border-secondary rounded""> ${routingLink.innerText} </li>`);
                    routingLinksElement.innerHTML = routingLinksListHTML;
                    
                    brButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                    

                    const nodesRegExp = /fd\S*\s/gi
                    var nodesAddr = [];
                    let regExpResults = text.match(nodesRegExp);

                    if (nodesAddr != null) {
                        regExpResults = regExpResults.map((node) => node.slice(0, -1))
                        regExpResults.forEach((node, index) => {
                            if (index % 2  == 0) {
                                nodesAddr.push(node)
                            }
                        })
                        console.log(nodesAddr);
                    }


                    

                    // NODES
                    





                    nodesDiv.classList.remove('border-secondary', 'border-success', 'border-warning', 'border-danger');
                    nodesDiv.classList.add('border-info');

                    nodesButtonIndex.classList.replace('d-none', 'd-block');
                    
                    nodesH1.classList.replace('text-muted', 'text-light');

                    
                    
                    
                    
                    
                    

                    nodesButtonIndex.addEventListener('click', () => {
                        
                        nodesButtonIndex.classList.replace('d-block', 'd-none')
                        nodesInput.innerHTML = nodesInputHTML(nodesAddr);

                        nodesAddr.forEach((node, index) => {

                            document.getElementById(`nodes-button-${index}`).addEventListener('click', () => {
    
                                console.log('getgetget');
                                let addr = document.getElementById(`nodes-addr-input-${index}`).value;
                                let path = document.getElementById(`nodes-path-input-${index}`).value;
                                
                                fetch(`http://[${addr}]/${path}`)
                                    
                                    .then(function(response) {
                                        
                                        return response.text()
                                    })
                                        
                                        .then(function(text) {
                                            
                                            nodesDiv.classList.remove('border-danger', 'border-warning', 'border-info'); nodesDiv.classList.add('border-success');
                                            
                                            document.getElementById(`nodes-output-${index}`).innerText = 'OK';

                                            document.getElementById(`nodes-output-${index}`).classList.remove('bg-danger', 'bg-warning'); document.getElementById(`nodes-output-${index}`).classList.add('bg-success');
                                            document.getElementById(`nodes-output-${index}`).classList.replace('d-none', 'd-block')
                                            
                                            
                                            
                                            
                                            document.getElementById('nodes-h2-encoded-response').classList.replace('d-none', 'd-block')
    
                                            nodesEncodedResponseDiv.classList.replace('d-none', 'd-block')
                                            nodesEncodedResponseDiv.innerText = text;
                                            


                                            nodesButtonDecode.classList.replace('btn-muted', 'btn-primary');
                                            nodesButtonDecode.classList.replace('d-none', 'd-block')
                                            nodesButtonDecode.addEventListener('click', () => {
                                                
                                                let decodedResponse = constructDecoding(text);
                                                
                                                nodesKeySpan.classList.replace('d-none', 'd-block');
                                                nodesKeyInput.classList.replace('d-none', 'd-block');

                                                nodesButtonDecrypt.classList.replace('btn-muted', 'btn-primary');
                                                nodesButtonDecrypt.classList.replace('d-none', 'd-block')
                                                nodesButtonDecrypt.addEventListener('click', () => {
    
                                                    let decryptedResponse = constructDecryption(decodedResponse);
                                                    let intact = checksum(decryptedResponse);
    
                                                    

                                                    nodesButtonChecksum.classList.replace('btn-muted', 'btn-primary');
                                                    nodesButtonChecksum.classList.replace('d-none', 'd-block');
                                                    nodesButtonChecksum.addEventListener('click', () => {
    
                                                        if(intact) {
                                                            constructIntactness(); 
                                                        } else {
                                                            constructCorruptness();
                                                        }
                                                    })
                                                    
                                                    nodesButtonParse.classList.replace('btn-muted', 'btn-primary');
                                                    nodesButtonParse.classList.replace('d-none', 'd-block');
                                                    nodesButtonParse.addEventListener('click', () => {
                                                        
                                                        try{
                                                            
                                                            let parsedResponse = JSON.parse(decryptedResponse);

                                                            constructParse_OK(parsedResponse);
                                                            constructLegend(parsedResponse, intact);
    
                                                        } 
                                                        catch(error) {
                                                            
                                                            constructParse_FAIL(error);

                                                        }
                                                    })
                                                })
                                            })
                                        })
                                    
                                    .catch(function(error) {

                                        nodesDiv.classList.remove('border-warning', 'border-success', 'border-info'); nodesDiv.classList.add('border-danger');
                                    
                                        document.getElementById(`nodes-output-${index}`).innerText = error;

                                        document.getElementById(`nodes-output-${index}`).classList.remove('bg-warning', 'bg-success'); document.getElementById(`nodes-output-${index}`).classList.add('bg-danger');
                                        document.getElementById(`nodes-output-${index}`).classList.replace('d-none', 'd-block')
                                        
                                        console.log(error);
                                    }
                                )  
                            })
                        })
                    })
                    
                    
                    
                    
                    
                    





                    // nodesAddr.forEach((node, index) => {

                    //     document.getElementById(`nodes-button-${index}`).addEventListener('click', () => {

                    //         console.log('getgetget');
                    //         let addr = document.getElementById(`nodes-addr-input-${index}`).value;
                    //         let path = document.getElementById(`nodes-path-input-${index}`).value;
                            
                    //         fetch(`http://[${addr}]/${path}`)
                    //             .then(function(response) {
                                    
                    //                 return response.text()
                    //             })
                    //                 .then(function(text) {
                    //                     console.log(text);

                    //                     nodesDiv.classList.remove('border-info');
                    //                     nodesDiv.classList.remove('border-warning');
                    //                     nodesDiv.classList.remove('border-danger');
                    //                     nodesDiv.classList.add('border-success');

                    //                     document.getElementById(`nodes-output-${index}`).innerText = 'OK';
                                        
                    //                     document.getElementById(`nodes-output-${index}`).classList.remove('bg-warning');
                    //                     document.getElementById(`nodes-output-${index}`).classList.remove('bg-danger');
                    //                     document.getElementById(`nodes-output-${index}`).classList.add('bg-success');
                    //                     document.getElementById(`nodes-output-${index}`).classList.replace('d-none', 'd-block')
                                        
                    //                     document.getElementById('nodes-h2-encoded-response').classList.replace('d-none', 'd-block')

                    //                     nodesEncodedResponseDiv.classList.replace('d-none', 'd-block')
                    //                     nodesEncodedResponseDiv.innerText = text;

                    //                     nodesButtonDecode.classList.replace('d-none', 'd-block')

                                        

                    //                     // nodesButtonClear.addEventListener('click', () => {
                                        
                    //                     //     nodesDiv.classList.replace('border-success', 'border-primary');
                    //                     //     nodesEncodedResponseDiv.innerText = '';

                    //                     // })
                    
                    //                     nodesButtonDecode.addEventListener('click', () => {
                                            
                    //                         nodesEncodedResponseDiv.classList.replace('text-light', 'text-dark')
                    //                         nodesButtonDecode.classList.replace('btn-primary', 'btn-outline-success')

                                            
                    //                         let decodedResponse = atob(text);

                    //                         // document.getElementById('nodes-h2-encrypted-response').classList.replace('d-none', 'd-block')

                                            
                                        
                    //                         nodesEncryptedResponseDiv.classList.replace('d-none', 'd-block')
                    //                         nodesEncryptedResponseDiv.innerText = decodedResponse;

                    //                         nodesButtonDecrypt.classList.replace('d-none', 'd-block')

                    //                         // nodesButtonClear.addEventListener('click', () => {
                                        
                    //                         //     nodesDiv.classList.replace('border-success', 'border-primary');
                    //                         //     nodesEncodedResponseDiv.innerText = '';
                                                
                    //                         //     nodesEncodedResponseDiv.classList.replace('text-dark', 'text-light')
                    //                         //     nodesButtonDecode.classList.replace('btn-success', 'btn-outline-primary')
                    //                         //     nodesEncryptedResponseDiv.innerText= ''
    
                    //                         // })

                    //                         nodesButtonDecrypt.addEventListener('click', () => {

                    //                             nodesEncryptedResponseDiv.classList.replace('text-light', 'text-dark')
                    //                             nodesButtonDecrypt.classList.replace('btn-primary', 'btn-outline-success')
                                                
                    //                             function oarCrypt(input) {
                    //                                 var key = ['!', '@', '#', '$', '%', '^', '&', '*'];
                    //                                 var output = [];
                                                    
                    //                                 for (var i = 0; i < input.length; i++) {
                    //                                     var charCode = input.charCodeAt(i) ^ (key[i % key.length].charCodeAt(0));
                    //                                     output.push(String.fromCharCode(charCode));
                    //                                 }
                    //                                 return output.join("");
                    //                             }

                    //                             let decryptedResponse = oarCrypt(decodedResponse);
                                                
                                                
                                        
                    //                             nodesStringifiedResponseDiv.classList.replace('d-none', 'd-block')
                    //                             nodesStringifiedResponseDiv.innerText = decryptedResponse;

                    //                             nodesButtonParse.classList.replace('d-none', 'd-block')
                    //                             nodesButtonChecksum.classList.replace('d-none', 'd-block')

                                                

                    //                             // nodesButtonClear.addEventListener('click', () => {
                                        
                    //                             //     nodesDiv.classList.replace('border-success', 'border-primary');
                    //                             //     nodesEncodedResponseDiv.innerText = '';
                                                    
                    //                             //     nodesEncodedResponseDiv.classList.replace('text-dark', 'text-light')
                    //                             //     nodesButtonDecode.classList.replace('btn-outline-success', 'btn-primary')
                    //                             //     nodesEncryptedResponseDiv.innerText= ''

                    //                             //     nodesEncryptedResponseDiv.classList.replace('text-dark', 'text-light')
                    //                             //     nodesButtonDecrypt.classList.replace('btn-outline-success', 'btn-primary')

                    //                             //     nodesStringifiedResponseDiv.innerText = '';

                    //                             // })

                    //                             let obj = JSON.parse(decryptedResponse);
                    //                             let payloadHash = obj.hash;
                    //                             let goa = obj;
                    //                             delete goa.hash;
                    //                             goa = JSON.stringify(goa);
                    //                             let intact = sdbm(goa.substr(0, goa.length -1) + "," ) == payloadHash ? true : false;
                    //                             console.log(intact);

                    //                             nodesButtonChecksum.addEventListener('click', () => {

                    //                                 if(intact) {
                    //                                     nodesButtonChecksum.classList.replace('btn-primary', 'btn-outline-success')
                                                        
                    //                                     nodesOutputChecksum.innerText = 'INTACT';

                    //                                     nodesOutputChecksum.classList.remove('bg-danger');
                    //                                     nodesOutputChecksum.classList.remove('bg-warning');
                    //                                     nodesOutputChecksum.classList.add('bg-success');
                    //                                     nodesOutputChecksum.classList.replace('d-none', 'd-block')
                    //                                 } else {
                    //                                     nodesButtonChecksum.classList.replace('btn-primary', 'btn-outline-danger')
                                                        
                    //                                     nodesOutputChecksum.innerText = 'CORRUPTED';

                    //                                     nodesOutputChecksum.classList.remove('bg-success');
                    //                                     nodesOutputChecksum.classList.remove('bg-danger');
                    //                                     nodesOutputChecksum.classList.add('bg-warning');
                    //                                     nodesOutputChecksum.classList.replace('d-none', 'd-block')

                    //                                     nodesDiv.classList.remove('bg-success');
                    //                                     nodesDiv.classList.remove('bg-danger');
                    //                                     nodesDiv.classList.add('bg-warning');
                    //                                 }
                    //                             })
                                                
                    //                             nodesButtonParse.addEventListener('click', () => {
                    //                                 try{
                    //                                     var parsedResponse = JSON.parse(decryptedResponse);
                    //                                     nodesButtonParse.classList.replace('btn-primary', 'btn-outline-success');

                                                        
                                                        
                    //                                     nodesParsedResponseDiv.classList.replace('d-none', 'd-block');

                    //                                     nodesParsedResponseDiv.innerHTML = JSON.stringify(parsedResponse, null, 2);

                    //                                     console.log(syntaxHighlight(parsedResponse));

                    //                                     nodesEncodedResponseDiv.classList.replace('text-dark', 'text-secondary')
                    //                                     nodesEncodedResponseDiv.classList.replace('bg-secondary', 'bg-dark')
                    //                                     nodesEncodedResponseDiv.classList.replace('border-dark', 'border-secondary')
                                                        
                    //                                     nodesEncryptedResponseDiv.classList.replace('text-dark', 'text-secondary')
                    //                                     nodesEncryptedResponseDiv.classList.replace('bg-secondary', 'bg-dark')
                    //                                     nodesEncryptedResponseDiv.classList.replace('border-dark', 'border-secondary')

                    //                                     nodesButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                    //                                     nodesButtonDecode.classList.replace('btn-outline-success', 'btn-outline-secondary')
                    //                                     nodesButtonDecrypt.classList.replace('btn-outline-success', 'btn-outline-secondary')
                    //                                     nodesButtonChecksum.classList.replace('btn-outline-success', 'btn-outline-secondary')

                    //                                     // nodesButtonClear.addEventListener('click', () => {
                                        
                    //                                     //     nodesDiv.classList.replace('border-success', 'border-primary');
                    //                                     //     nodesEncodedResponseDiv.innerText = '';
                    //                                     //     nodesButtonDecode.classList.replace('d-block', 'd-none');
                    //                                     //     nodesDiv.classList.replace('d-block', 'd-none')
                                                            
                    //                                     //     nodesEncodedResponseDiv.classList.replace('text-dark', 'text-light')
                    //                                     //     nodesButtonDecode.classList.replace('btn-success', 'btn-outline-primary')
                    //                                     //     nodesEncryptedResponseDiv.classList.replace('d-block', 'd-node')
                    //                                     //     nodesEncryptedResponseDiv.innerText= ''
        
                    //                                     //     nodesEncryptedResponseDiv.classList.replace('text-dark', 'text-light')
                    //                                     //     nodesButtonDecrypt.classList.replace('btn-outline-success', 'btn-primary')
        
                    //                                     //     nodesStringifiedResponseDiv.classList.replace('d-block', 'd-none')
                    //                                     //     nodesStringifiedResponseDiv.innerText = '';
        
                    //                                     //     nodesButtonParse.classList.replace('d-block', 'd-none')
                    //                                     //     nodesButtonChecksum.classList.replace('d-block', 'd-none')

                    //                                     //     nodesOutputChecksum.classList.replace('d-block', 'd-none')
                    //                                     //     nodesButtonParse.classList.replace('btn-outline-success', 'btn-primary');
                    //                                     //     nodesParsedResponseDiv.classList.replace('d-block', 'd-none');
                    //                                     //     nodesParsedResponseDiv.innerHTML = ''
        
                    //                                     // })
                                                        
                    //                                     // CONTINUE FROM HERE TOMORROW

                                                        

                    //                                     constructLegend(parsedResponse, intact);


                    //                                 } catch(error) {
                    //                                     nodesButtonParse.classList.replace('btn-primary', 'btn-outline-danger');

                    //                                     nodesDiv.classList.remove('bg-warning');
                    //                                     nodesDiv.classList.remove('bg-danger');
                    //                                     nodesDiv.classList.add('bg-danger');

                    //                                     nodesOutputChecksum.innerText = error;

                    //                                     nodesOutputChecksum.classList.remove('bg-success');
                    //                                     nodesOutputChecksum.classList.remove('bg-warning');
                    //                                     nodesOutputChecksum.classList.add('bg-danger');
                    //                                     nodesOutputChecksum.classList.replace('d-none', 'd-block')
                    //                                 }
                    //                             })
                    //                         })
                    //                     })
                    //                 })
                    //             .catch(function(error) {

                                    
                                    
                    //                 nodesDiv.classList.remove('border-info');
                    //                 nodesDiv.classList.remove('border-success');
                    //                 nodesDiv.classList.remove('border-warning');
                    //                 nodesDiv.classList.add('border-danger');

                    //                 document.getElementById(`nodes-output-${index}`).innerText = error;
                                        
                    //                 document.getElementById(`nodes-output-${index}`).classList.remove('bg-success');
                    //                 document.getElementById(`nodes-output-${index}`).classList.remove('bg-warning');
                    //                 document.getElementById(`nodes-output-${index}`).classList.add('bg-danger');
                    //                 document.getElementById(`nodes-output-${index}`).classList.replace('d-none', 'd-block')
                                    
                    //                 console.log(error);
                    //             }
                    //         )
                            
                    //     })
                    // })
                    
            } catch {
                
                if(uls.length < 2) {

                    brDiv.classList.remove('border-info');
                    brDiv.classList.remove('border-success');
                    brDiv.classList.remove('border-danger');
                    brDiv.classList.add('border-warning');

                    brOutput.innerText = 'warning: detected neighbor data are incomplete.';

                    brOutput.classList.remove('bg-danger');
                    brOutput.classList.remove('bg-success');
                    brOutput.classList.add('bg-warning');
                    brOutput.classList.replace('d-none', 'd-block')

                    brButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-muted');

                }
            }
        })
        .catch(function(error) {

            brDiv.classList.remove('border-info');
            brDiv.classList.remove('border-success');
            brDiv.classList.remove('border-warning');
            brDiv.classList.add('border-danger');

            brOutput.innerText = error;
            
            brOutput.classList.remove('bg-success');
            brOutput.classList.remove('bg-warning');
            brOutput.classList.add('bg-danger');
            brOutput.classList.replace('d-none', 'd-block')
            console.log(error);
        })
}

function simConsole(nodesAddr) {
    console.log(nodesAddr);
}


function constructLegend(obj, intact) {

    let elaboratedObj = elaborate(obj, intact);
    console.log(elaboratedObj);

}

function elaborate(obj, intact) {

    if(obj.pckt.vld === true) {

        switch(obj.ndx) {

            case 0: 
                var system = {
                    packet: {
                        valid: obj.pckt.vld,
                        error: null
                    },
                    record: obj.rcrd,
                    index: obj.ndx,
                    mote: {
                        systemTime: obj.id.sT,
                        linkLayerAddress: obj.id.adr,
                        moteCode: obj.id.cd
                    },
                    system: {
                        contikiVersion: obj.sys.cV,
                        networkStackRouting: obj.sys.rt,
                        networkStackNetwork: obj.sys.net,
                        ieee802154PANID: obj.sys.pId,
            
                        networkStackMac: {
                            name: obj.sys.mac.t,
                            tschDefaultHoppingSequence: obj.sys.mac.tDhS,
                            defaultChannel: obj.sys.mac.dCh
                        },
                        nodeId: obj.sys.nId,
                        tentaticeLinkLocalIPv6address: obj.sys.tIad
                    },
                    checksum: {
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                return system;
        }
    }

}