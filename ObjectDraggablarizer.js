// author langenhagen
// found here http://stackoverflow.com/questions/6914360/how-to-scroll-through-a-div-by-dragging-and-not-by-using-the-scroll-bars
// 160621

function ObjectDraggablarizer( dragElement) {

    var self = this;

    self.startY      = 0;
    self.offsetY     = 0;
    self.dragElement = dragElement;
    self.oldClientY  = 0;


    self.OnMouseDown = function (event) {
        self.dragElement.onmousemove = self.OnMouseMove;
        self.oldClientY = event.clientY;
    }

    self.OnMouseMove = function (event) {

        self.dragElement.scrollTop += self.oldClientY - event.clientY;
        self.oldClientY = event.clientY;

        if( event.clientX < self.dragElement.offsetLeft ||
            event.clientX >= self.dragElement.clientWidth + self.dragElement.offsetLeft ||
            event.clientY < self.dragElement.offsetTop ||
            event.clientY >= self.dragElement.clientHeight + self.dragElement.offsetTop) {
            self.OnMouseUp(event);
        }
    }

    self.OnMouseUp = function (event) {
        dragElement.onmousemove = null;
    }

    self.dragElement.onmousedown = self.OnMouseDown;
    self.dragElement.onmouseup = self.OnMouseUp;
}