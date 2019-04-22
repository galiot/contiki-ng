// https://stackoverflow.com/questions/36631762/returning-html-with-fetch
// https://stackoverflow.com/a/50812705

// https://www.codecademy.com/articles/what-is-cors

// http://[fd00::212:4b00:f24:8385]/

console.log('hello world');



const brUrlButton = document.getElementById('br-url-button');
brUrlButton.addEventListener('click', scrap);

function scrap() {
    const brUrlInput = document.getElementById('br-url-input');
    const scrapMessage = document.getElementById('scrap-message');
    console.log(brUrlInput.value);

    fetch(`http://${brUrlInput.value}/`)
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

                neighborsNodeList = uls[0].querySelectorAll('li');
                neighborsArray = Array.from(neighborsNodeList);

                routingLinksNodeList = uls[1].querySelectorAll('li');
                routingLinksArray = Array.from(routingLinksNodeList);
                
                console.log(neighborsArray);
                console.log(routingLinksArray);

                scrapMessage.innerText = 'OK';

                scrapMessage.classList.remove('bg-danger');
                scrapMessage.classList.add('bg-success');
                scrapMessage.classList.replace('d-none', 'd-block')

                const neighborsElement = document.getElementById('neighbors');
                const routingLinksElement = document.getElementById('routing-links');

                neighborsElement.classList.replace('d-none', 'd-block');
                routingLinksElement.classList.replace('d-none', 'd-block');

                let neighborsListHTML = '';
                let routingLinksListHTML = '';

                neighborsArray.forEach((neighbor, index) => neighborsListHTML += `<li class=" list-group-item text-center bg-light"> ${neighbor.innerText} </li>`);
                neighborsElement.innerHTML = neighborsListHTML;

                routingLinksArray.forEach((routingLink, index) => routingLinksListHTML += `<li class=" list-group-item text-center bg-light"> ${routingLink.innerText} </li>`);
                routingLinksElement.innerHTML = routingLinksListHTML;

                const nodesRegExp = /fd\S*\s/gi
                let nodes = [];
                let matchingNodes = text.match(nodesRegExp);

                if (nodes != null) {
                    matchingNodes = matchingNodes.map((node) => node.slice(0, -1))
                    matchingNodes.forEach((node, index) => {
                        if (index % 2  == 0) {
                            nodes.push(node)
                        }
                    })
                    console.log(nodes);
                }

                const nodesButtons = document.getElementById('nodes-buttons');
                let nodesButtonsHTML = '';

                nodes.forEach((node, index) => {
                    nodesButtonsHTML += `<div class="col-auto">  <button class="btn btn-primary" type="button" id="node-${index}-button">${node}</button> </div>`
                })

                nodesButtons.innerHTML = nodesButtonsHTML;

            })
        .catch(function(error) {
            scrapMessage.innerText = error;
            scrapMessage.classList.remove('bg-success');
            scrapMessage.classList.add('bg-danger');
            scrapMessage.classList.replace('d-none', 'd-block')
            console.log(error);
        })
}