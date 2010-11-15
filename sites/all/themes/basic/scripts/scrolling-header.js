
// ***
// Scrolling background
// ***

// height of background image in pixels
var backgroundwidth = 1100;

// get the current minute/hour of the day
var now = new Date();
var hour = now.getHours();
var minute = now.getMinutes();

// work out how far through the day we are as a percentage - e.g. 6pm = 75%
var hourpercent = hour / 24 * 100;
var minutepercent = minute / 60 / 24 * 100;
var percentofday = Math.round(hourpercent + minutepercent);

// calculate which pixel row to start graphic from based
// on how far through the day we are
var offset = backgroundwidth / 100 * percentofday;

// graphic starts at approx 6am, so adjust offset by 1/4
var offset = offset - (backgroundwidth / 4);

function scrollbackground() {
	// decrease the offset by 1, or if its less than 1 increase it by
	// the background height minus 1
	offset = (offset < 1) ? offset + (backgroundwidth - 1) : offset - 1;
	// apply the background position
	$('#header').css("background-position", offset + "px " + "0");
	// call self to continue animation
	setTimeout(function() {
		scrollbackground();
		}, 100
	);
}

// Start the animation
scrollbackground();