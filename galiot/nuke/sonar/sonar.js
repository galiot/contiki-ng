// https://github.com/sindresorhus/sdbm
const sdbm = string => {
	let hash = 0;

	for (let i = 0; i < string.length; i++) {
		hash = string.charCodeAt(i) + (hash << 6) + (hash << 16) - hash;
	}

	// Convert it to an unsigned 32-bit integer
	return hash >>> 0;
};

// https://stackoverflow.com/a/7220510
function syntaxHighlight(json) {
    if (typeof json != 'string') {
         json = JSON.stringify(json, undefined, 2);
    }
    json = json.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
    return json.replace(/("(\\u[a-zA-Z0-9]{4}|\\[^u]|[^\\"])*"(\s*:)?|\b(true|false|null)\b|-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?)/g, function (match) {
        var cls = 'number';
        if (/^"/.test(match)) {
            if (/:$/.test(match)) {
                cls = 'key';
            } else {
                cls = 'string';
            }
        } else if (/true|false/.test(match)) {
            cls = 'boolean';
        } else if (/null/.test(match)) {
            cls = 'null';
        }
        return '<span class="' + cls + '">' + match + '</span>';
    });
}


// https://stackoverflow.com/questions/36631762/returning-html-with-fetch
// https://stackoverflow.com/a/50812705

// https://www.codecademy.com/articles/what-is-cors

// http://[fd00::212:4b00:f24:8385]/

console.log('hello world');

const brDiv = document.getElementById('br-div');
const brButton = document.getElementById('br-button');
const brButtonReload = document.getElementById('br-button-reload');
const brButtonClear = document.getElementById('br-button-clear');
const brButtonContinue = document.getElementById('br-button-continue');
const nodesButtonReload = document.getElementById('nodes-button-reload');
const nodesButtonClear = document.getElementById('nodes-button-clear');
const nodesButtonContinue = document.getElementById('nodes-button-continue');

const nodesDiv = document.getElementById('nodes-div');
const nodesH1 = document.getElementById('nodes-h1');

brButton.addEventListener('click', scrap);

brButtonReload.addEventListener('click', () => {
    event.preventDefault();
    window.location.reload(true);
});
nodesButtonReload.addEventListener('click', () => {
    event.preventDefault();
    window.location.reload(true);
});







brButtonContinue.addEventListener('click', () => nodesDiv.classList.replace('d-none', 'd-block'))

function scrap() {
    const brInput = document.getElementById('br-input');
    const brOutput = document.getElementById('br-output');
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

                    brDiv.classList.remove('border-info');
                    brDiv.classList.remove('border-warning');
                    brDiv.classList.remove('border-danger');
                    brDiv.classList.add('border-success');
                    
                    brOutput.innerText = 'OK';

                    brOutput.classList.remove('bg-danger');
                    brOutput.classList.remove('bg-warning');
                    brOutput.classList.add('bg-success');
                    brOutput.classList.replace('d-none', 'd-block')

                    document.getElementById('br-h2-neighbors').classList.replace('d-none', 'd-block')
                    document.getElementById('br-h2-routing-links').classList.replace('d-none', 'd-block')
                    
                    const neighborsElement = document.getElementById('neighbors');
                    const routingLinksElement = document.getElementById('routing-links');

                    neighborsElement.classList.replace('d-none', 'd-block');
                    routingLinksElement.classList.replace('d-none', 'd-block');

                    let neighborsListHTML = '';
                    let routingLinksListHTML = '';

                    neighborsArray.forEach((neighbor, index) => neighborsListHTML += `<li class="list-group-item text-center bg-dark text-light border-secondary rounded"> ${neighbor.innerText} </li>`);
                    neighborsElement.innerHTML = neighborsListHTML;

                    routingLinksArray.forEach((routingLink, index) => routingLinksListHTML += `<li class="list-group-item text-center bg-dark text-light border-secondary rounded""> ${routingLink.innerText} </li>`);
                    routingLinksElement.innerHTML = routingLinksListHTML;
                    
                    brButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                    brButtonClear.addEventListener('click', () => {
                        
                        neighborsElement.innerHTML = '';
                        routingLinksElement.innerHTML = '';
                        brDiv.classList.replace('border-success', 'border-primary');
                        brOutput.classList.replace('d-block', 'd-none')

                        document.getElementById('br-h2-neighbors').classList.replace('d-block', 'd-none')
                        document.getElementById('br-h2-routing-links').classList.replace('d-block', 'd-none')

                    })

                    const nodesRegExp = /fd\S*\s/gi
                    let nodesAddr = [];
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
                    nodesH1.classList.replace('text-muted', 'text-light');

                    const nodesInput = document.getElementById('nodes-input');
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
                    

                    nodesInput.innerHTML = nodesInputHTML;

                    nodesAddr.forEach((node, index) => {
                        document.getElementById(`nodes-button-${index}`).addEventListener('click', () => {
                            let path = document.getElementById(`nodes-path-input-${index}`).value;
                            
                            fetch(`http://[${node}]/${path}`)
                                .then(function(response) {
                                    return response.text()
                                })
                                    .then(function(text) {
                                        console.log(text);

                                        nodesDiv.classList.remove('border-info');
                                        nodesDiv.classList.remove('border-warning');
                                        nodesDiv.classList.remove('border-danger');
                                        nodesDiv.classList.add('border-success');

                                        document.getElementById(`nodes-output-${index}`).innerText = 'OK';
                                        
                                        document.getElementById(`nodes-output-${index}`).classList.remove('bg-warning');
                                        document.getElementById(`nodes-output-${index}`).classList.remove('bg-danger');
                                        document.getElementById(`nodes-output-${index}`).classList.add('bg-success');
                                        document.getElementById(`nodes-output-${index}`).classList.replace('d-none', 'd-block')
                                        
                                        document.getElementById('nodes-h2-encoded-response').classList.replace('d-none', 'd-block')

                                        const nodesEncodedResponseDiv = document.getElementById('nodes-encoded-response-div');
                                        const nodesButtonDecode = document.getElementById('nodes-button-decode');
                                        
                                        nodesEncodedResponseDiv.classList.replace('d-none', 'd-block')
                                        nodesEncodedResponseDiv.innerText = text;

                                        nodesButtonDecode.classList.replace('d-none', 'd-block')

                                        var globalIndex = index;

                                        nodesButtonClear.addEventListener('click', () => {
                                        
                                            nodesDiv.classList.replace('border-success', 'border-primary');
                                            nodesEncodedResponseDiv.innerText = '';

                                        })
                    
                                        nodesButtonDecode.addEventListener('click', () => {
                                            
                                            nodesEncodedResponseDiv.classList.replace('text-light', 'text-dark')
                                            nodesButtonDecode.classList.replace('btn-primary', 'btn-outline-success')

                                            
                                            let decodedResponse = atob(text);

                                            // document.getElementById('nodes-h2-encrypted-response').classList.replace('d-none', 'd-block')

                                            const nodesEncryptedResponseDiv = document.getElementById('nodes-encrypted-response-div');
                                            const nodesButtonDecrypt = document.getElementById('nodes-button-decrypt');
                                        
                                            nodesEncryptedResponseDiv.classList.replace('d-none', 'd-block')
                                            nodesEncryptedResponseDiv.innerText = decodedResponse;

                                            nodesButtonDecrypt.classList.replace('d-none', 'd-block')

                                            nodesButtonClear.addEventListener('click', () => {
                                        
                                                nodesDiv.classList.replace('border-success', 'border-primary');
                                                nodesEncodedResponseDiv.innerText = '';
                                                
                                                nodesEncodedResponseDiv.classList.replace('text-dark', 'text-light')
                                                nodesButtonDecode.classList.replace('btn-success', 'btn-outline-primary')
                                                nodesEncryptedResponseDiv.innerText= ''
    
                                            })

                                            nodesButtonDecrypt.addEventListener('click', () => {

                                                nodesEncryptedResponseDiv.classList.replace('text-light', 'text-dark')
                                                nodesButtonDecrypt.classList.replace('btn-primary', 'btn-outline-success')
                                                
                                                function oarCrypt(input) {
                                                    var key = ['!', '@', '#', '$', '%', '^', '&', '*'];
                                                    var output = [];
                                                    
                                                    for (var i = 0; i < input.length; i++) {
                                                        var charCode = input.charCodeAt(i) ^ (key[i % key.length].charCodeAt(0));
                                                        output.push(String.fromCharCode(charCode));
                                                    }
                                                    return output.join("");
                                                }

                                                let decryptedResponse = oarCrypt(decodedResponse);
                                                
                                                const nodesStringifiedResponseDiv = document.getElementById('nodes-stringified-response-div');
                                                const nodesButtonParse = document.getElementById('nodes-button-parse');
                                                const nodesButtonChecksum = document.getElementById('nodes-button-checksum');
                                        
                                                nodesStringifiedResponseDiv.classList.replace('d-none', 'd-block')
                                                nodesStringifiedResponseDiv.innerText = decryptedResponse;

                                                nodesButtonParse.classList.replace('d-none', 'd-block')
                                                nodesButtonChecksum.classList.replace('d-none', 'd-block')

                                                const nodesOutputChecksum = document.getElementById('nodes-output-checksum')

                                                // nodesButtonClear.addEventListener('click', () => {
                                        
                                                //     nodesDiv.classList.replace('border-success', 'border-primary');
                                                //     nodesEncodedResponseDiv.innerText = '';
                                                    
                                                //     nodesEncodedResponseDiv.classList.replace('text-dark', 'text-light')
                                                //     nodesButtonDecode.classList.replace('btn-outline-success', 'btn-primary')
                                                //     nodesEncryptedResponseDiv.innerText= ''

                                                //     nodesEncryptedResponseDiv.classList.replace('text-dark', 'text-light')
                                                //     nodesButtonDecrypt.classList.replace('btn-outline-success', 'btn-primary')

                                                //     nodesStringifiedResponseDiv.innerText = '';

                                                // })

                                                nodesButtonChecksum.addEventListener('click', () => {
                                                    let obj = JSON.parse(decryptedResponse);
                                                    let payloadHash = obj.hash;
                                                    let goa = obj;
                                                    delete goa.hash;
                                                    goa = JSON.stringify(goa);
                                                    let intact = sdbm(goa.substr(0, goa.length -1) + "," ) == payloadHash ? true : false;
                                                    console.log(intact);

                                                    if(intact) {
                                                        nodesButtonChecksum.classList.replace('btn-primary', 'btn-outline-success')
                                                        
                                                        nodesOutputChecksum.innerText = 'INTACT';

                                                        nodesOutputChecksum.classList.remove('bg-danger');
                                                        nodesOutputChecksum.classList.remove('bg-warning');
                                                        nodesOutputChecksum.classList.add('bg-success');
                                                        nodesOutputChecksum.classList.replace('d-none', 'd-block')
                                                    } else {
                                                        nodesButtonChecksum.classList.replace('btn-primary', 'btn-outline-danger')
                                                        
                                                        nodesOutputChecksum.innerText = 'CORRUPTED';

                                                        nodesOutputChecksum.classList.remove('bg-success');
                                                        nodesOutputChecksum.classList.remove('bg-danger');
                                                        nodesOutputChecksum.classList.add('bg-warning');
                                                        nodesOutputChecksum.classList.replace('d-none', 'd-block')

                                                        nodesDiv.classList.remove('bg-success');
                                                        nodesDiv.classList.remove('bg-danger');
                                                        nodesDiv.classList.add('bg-warning');
                                                    }
                                                })
                                                
                                                nodesButtonParse.addEventListener('click', () => {
                                                    try{
                                                        var parsedResponse = JSON.parse(decryptedResponse);
                                                        nodesButtonParse.classList.replace('btn-primary', 'btn-outline-success');

                                                        const nodesParsedResponseDiv = document.getElementById('nodes-parsed-response-div');
                                                        
                                                        nodesParsedResponseDiv.classList.replace('d-none', 'd-block');

                                                        nodesParsedResponseDiv.innerHTML = JSON.stringify(parsedResponse, null, 2);

                                                        console.log(syntaxHighlight(parsedResponse));

                                                        nodesEncodedResponseDiv.classList.replace('text-dark', 'text-secondary')
                                                        nodesEncodedResponseDiv.classList.replace('bg-secondary', 'bg-dark')
                                                        nodesEncodedResponseDiv.classList.replace('border-dark', 'border-secondary')
                                                        
                                                        nodesEncryptedResponseDiv.classList.replace('text-dark', 'text-secondary')
                                                        nodesEncryptedResponseDiv.classList.replace('bg-secondary', 'bg-dark')
                                                        nodesEncryptedResponseDiv.classList.replace('border-dark', 'border-secondary')

                                                        nodesButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                                                        nodesButtonDecode.classList.replace('btn-outline-success', 'btn-outline-secondary')
                                                        nodesButtonDecrypt.classList.replace('btn-outline-success', 'btn-outline-secondary')
                                                        nodesButtonChecksum.classList.replace('btn-outline-success', 'btn-outline-secondary')

                                                        // nodesButtonClear.addEventListener('click', () => {
                                        
                                                        //     nodesDiv.classList.replace('border-success', 'border-primary');
                                                        //     nodesEncodedResponseDiv.innerText = '';
                                                        //     nodesButtonDecode.classList.replace('d-block', 'd-none');
                                                        //     nodesDiv.classList.replace('d-block', 'd-none')
                                                            
                                                        //     nodesEncodedResponseDiv.classList.replace('text-dark', 'text-light')
                                                        //     nodesButtonDecode.classList.replace('btn-success', 'btn-outline-primary')
                                                        //     nodesEncryptedResponseDiv.classList.replace('d-block', 'd-node')
                                                        //     nodesEncryptedResponseDiv.innerText= ''
        
                                                        //     nodesEncryptedResponseDiv.classList.replace('text-dark', 'text-light')
                                                        //     nodesButtonDecrypt.classList.replace('btn-outline-success', 'btn-primary')
        
                                                        //     nodesStringifiedResponseDiv.classList.replace('d-block', 'd-none')
                                                        //     nodesStringifiedResponseDiv.innerText = '';
        
                                                        //     nodesButtonParse.classList.replace('d-block', 'd-none')
                                                        //     nodesButtonChecksum.classList.replace('d-block', 'd-none')

                                                        //     nodesOutputChecksum.classList.replace('d-block', 'd-none')
                                                        //     nodesButtonParse.classList.replace('btn-outline-success', 'btn-primary');
                                                        //     nodesParsedResponseDiv.classList.replace('d-block', 'd-none');
                                                        //     nodesParsedResponseDiv.innerHTML = ''
        
                                                        // })
                                                        
                                                        // CONTINUE FROM HERE TOMORROW

                                                    } catch(error) {
                                                        nodesButtonParse.classList.replace('btn-primary', 'btn-outline-danger');

                                                        nodesDiv.classList.remove('bg-warning');
                                                        nodesDiv.classList.remove('bg-danger');
                                                        nodesDiv.classList.add('bg-danger');

                                                        nodesOutputChecksum.innerText = error;

                                                        nodesOutputChecksum.classList.remove('bg-success');
                                                        nodesOutputChecksum.classList.remove('bg-warning');
                                                        nodesOutputChecksum.classList.add('bg-danger');
                                                        nodesOutputChecksum.classList.replace('d-none', 'd-block')
                                                    }
                                                })
                                            })
                                        })
                                    })
                                .catch(function(error) {
                                    
                                    nodesDiv.classList.remove('border-info');
                                    nodesDiv.classList.remove('border-success');
                                    nodesDiv.classList.remove('border-warning');
                                    nodesDiv.classList.add('border-danger');

                                    document.getElementById(`nodes-output-${index}`).innerText = error;
                                        
                                    document.getElementById(`nodes-output-${index}`).classList.remove('bg-success');
                                    document.getElementById(`nodes-output-${index}`).classList.remove('bg-warning');
                                    document.getElementById(`nodes-output-${index}`).classList.add('bg-danger');
                                    document.getElementById(`nodes-output-${index}`).classList.replace('d-none', 'd-block')
                                    
                                    console.log(error);
                                }
                            )
                            
                        })
                    })
                    
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