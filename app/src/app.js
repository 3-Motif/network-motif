import { drawEdge, drawNode } from './render.js';
import Module from './graph.js';
const moduleInstance = await Module();

const canvasParentEl = document.querySelector('.canvas-wrapper')
const canvas = document.getElementById('mainCanvas')
const ctx = canvas.getContext('2d')
canvas.width = canvasParentEl.offsetWidth
canvas.height = canvasParentEl.offsetHeight

const fileUploadContainer = document.getElementById('fileUploadContainer')
const spinner = document.getElementById('loader')
const countSubgraphBtn = document.getElementById('countSubgraphBtn')
const genRandomBtn = document.getElementById('genRandomBtn')

spinner.style.display = 'none'


function getRandomInt(min, max) {
    if(!min || min < 0) min = 0
    return Math.floor(Math.random() * max) + min;
}

const subgraphContainer = document.getElementById('subgraphs')
const subgraphs = ['1 2\n1 3', '2 1\n3 1', '2 3\n3 1', '1 3\n2 1\n3 1', '1 2\n1 3\n 2 1', '1 2\n1 3\n 2 1\n 3 1', '1 2\n1 3\n2 3', '1 2\n2 3\n3 1', '1 2\n1 3\n2 3\n3 2', '2 1\n2 3\n3 1\n3 2', '1 2\n1 3\n2 3\n3 1', '1 3\n2 1\n2 3\n3 1\n3 2', '1 2\n1 3\n2 1\n2 3\n3 1\n3 2']
function drawSubgraphs(container){
	subgraphs.forEach((subgraph, index)=>{
		// create a canvas and its container
		const box = document.createElement('div')
		const miniCanvas = document.createElement('canvas')
		box.setAttribute('id', `subgraph${index}`)
		box.setAttribute('class', 'subgraph')
		miniCanvas.width = 120
		miniCanvas.height = 120

		const minictx = miniCanvas.getContext("2d")
		box.appendChild(miniCanvas)
		container.appendChild(box)


		const subgraphObj = new moduleInstance.Graph(subgraph)
		const order = subgraphObj.order()
		const subgraphNodes = []
		// render subgraph
		for (let n = 0; n < order; n++) {
			// arrange in circle of radius 40
			subgraphNodes[n] = {x : miniCanvas.offsetWidth/2 + 40* Math.cos(2* n *Math.PI /order) -5, y: miniCanvas.offsetHeight/2 + 40 * Math.sin(2* n *Math.PI /order)}
			drawNode(minictx, subgraphNodes[n], 10)
		}

		// draw egdes
		for (let row = 0; row < order; row++) {
			for(let col = 0; col <order; col++){
				if(subgraphObj.get(row, col) == 1){
					drawEdge(minictx, subgraphNodes[row], subgraphNodes[col])
				}
			}
			
		}
		subgraphObj.delete()
	})
}



const nodes=[]

// Handle file input
document.getElementById('upload').addEventListener('change', async (event) => {
	const file = event.target.files[0];
	if (!file) return;

	// Read file as text
	const text = await file.text(); 

	const graphObj = new moduleInstance.Graph(text);
	const order = graphObj.order()

	console.log("Graph order:", graphObj.order());
	console.log("Graph size:", graphObj.size());

	// render the graph
	// draw nodes
	for (let n = 0; n < order; n++) {
		nodes[n] = {x: getRandomInt(50, canvas.width-100), y: getRandomInt(50, canvas.height-100)}
		drawNode(ctx, nodes[n], 15)
	}

	// draw egdes
	for (let row = 0; row < order; row++) {
		for(let col = 0; col <order; col++){
			if(graphObj.get(row, col) == 1){
				drawEdge(ctx, nodes[row], nodes[col])
			}
		}
		
	}

	fileUploadContainer.style.display = 'none'

	drawSubgraphs(subgraphContainer)

	countSubgraphBtn.addEventListener('click', ()=>{
		spinner.style.display = 'flex'
		setTimeout(()=>{
			const counts = graphObj.getAllSubgraphCounts();
			for(let i = 0; i < subgraphs.length; i++){
				displaySubgraphCount(i, 'Real', counts.get(i))
			}
			spinner.style.display = 'none'
		},500)
	})

	genRandomBtn.addEventListener('click', ()=>{
		spinner.style.display = 'flex'

		setTimeout(()=>{
			const avgRandCounts = graphObj.getAllRandSubgraphAvgCounts(10);
			for(let i = 0; i < subgraphs.length; i++){
				displaySubgraphCount(i, 'μ(Random)', avgRandCounts.get(i))
			}	
			spinner.style.display = 'none'

		}, 200)


	})


	// need to use .get(index) to get value from std::vector -- cannot directly used as js array
	// for (let i = 0; i < 13; i++) {
	// 	console.log("subgraph",i+1,"count", "- [Real]:",counts.get(i), ", [Rand]:", randCounts.get(i));
	// }


	// mila: make a close button and delte this
	// graphObj.delete();
});



function displaySubgraphCount(index, text, num){
	const subgraphContainer = document.getElementById(`subgraph${index}`)
	if(!subgraphContainer) return

	const textNode = document.createElement('p')
	textNode.innerText = `${text}: ${num}`
	subgraphContainer.appendChild(textNode)
}
