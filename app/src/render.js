
export function drawNode(ctx, node,radius){
    ctx.save()
    ctx.beginPath()
    ctx.fillStyle = "#527caf"
    ctx.ellipse(node.x, node.y, radius, radius, 0, 0, 2 * Math.PI)
    ctx.fill()
    ctx.restore()
}

export function drawEdge(ctx, node1, node2){
    // draw line
    const angle = Math.atan2(node2.y-node1.y,node2.x-node1.x)
    node1 = {x: node1.x+(12 * Math.cos(angle)), y: node1.y+(12* Math.sin(angle))}

    node2 = {x: node2.x-(18 * Math.cos(angle)), y: node2.y-(18* Math.sin(angle))}

    ctx.strokeStyle = "#6f533e"
    ctx.lineWidth = 1
    ctx.beginPath()
    ctx.moveTo(node1.x, node1.y)
    ctx.lineTo(node2.x, node2.y)
    ctx.stroke()

    // draw arrow
    const size = 8;


    ctx.save();
    ctx.fillStyle = '#6f533e'

    //starting a new path from the head of the arrow to one of the sides of
    //the point
    ctx.beginPath();
    ctx.moveTo(node2.x, node2.y);
    ctx.lineTo(node2.x-size*Math.cos(angle-Math.PI/7),
               node2.y-size*Math.sin(angle-Math.PI/7));
 
    //path from the side point of the arrow, to the other side point
    ctx.lineTo(node2.x-size*Math.cos(angle+Math.PI/7),
               node2.y-size*Math.sin(angle+Math.PI/7));
 
    //path from the side point back to the tip of the arrow, and then
    //again to the opposite side point
    ctx.lineTo(node2.x, node2.y);
    ctx.lineTo(node2.x-size*Math.cos(angle-Math.PI/7),
               node2.y-size*Math.sin(angle-Math.PI/7));
 
    //draws the paths created above
    ctx.stroke();
    ctx.fill();
    ctx.restore();


}

