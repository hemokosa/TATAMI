
window.onload = function() {

//	var chart1 = new Chart.Bubble('chart1', {
//		width: 600,
//		height: 350,
//		lineColor: '#3f3f3f',
//		zmin: 0, zmax: 100,
//		bubbleSize: 40
//	});
	
//	chart1.bubbles = [
//		{x: 82, y: 70, z: 90, color: '#318bd6', tip: '<b>HTML</b> is allowed in <span style="color: #71a8d6;">tooltips</span>'},
//		{x: 21, y: 11, z: 0, color: '#000', tip: 'This bubble is the minimum size'},
//		{x: 0, y: 0, z: 50, color: '#ff0000', tip: 'Sun'},
//		{x: 10, y: 100, z: 50, color: '#959300', tip: 'Behind'},
//		{x: 12, y: 92, z: 40, color: '#802b60', tip: 'Smaller bubbles will render above bigger ones'},
//		{x: 100, y: 100, z: 100, color: '#1727a3', tip: '<i>Top</i> <b>Big</b> <u>Left</u>'},
//		{x: 50, y: 50, z: 50, color: '#1727a3', tip: 'Tooltips can have<br />multiple lines. Like this<br />And this'},
//	];
	
//	chart1.redraw();

//	$('emptyChart').addEvent('click', function() {
//		chart1.empty();
//	});


	var color = new Color([170, 0, 0]);
	var colorSlider = new Slider($('cslider'), $('cknob'), {
		steps: 300,
		onChange: function() {
			color = color.setHue(this.step);
			var c = color.hsbToRgb();
			$('cknob').set('text', color.rgbToHex()).setStyle('background-color', color);
		}
	}).set(20);

	var xSlider = new Slider($('xslider'), $('xknob'), {
		steps: 1000,
		onChange: function() {
			$('xknob').set('text', this.step-500);
		}
	}).set(500);

	var ySlider = new Slider($('yslider'), $('yknob'), {
		steps: 1000,
		onChange: function() {
			$('yknob').set('text', this.step-500);
		}
	}).set(500);

	var zSlider = new Slider($('zslider'), $('zknob'), {
		steps: 1000,
		onChange: function() {
			$('zknob').set('text', this.step-500);
		}
	}).set(500);
	
	$('addCustom').addEvent('click', function() {
		chart1.addBubble(
			$('xknob').get('text'),
			$('yknob').get('text'),
			$('zknob').get('text'),
			color.rgbToHex(),
			$('rutaTip').get('value')
		);
		chart1.redraw();
	});
	
	$('fancy').addEvent('click', function() {
		
		var i = 0;
		
		var boing = function() {
			var y = ((Math.sin(i/8)+1)*50).round();
			chart1.addBubble(i*4, y, 0, color.setSaturation(100-i), ''+y);
			chart1.redraw();
			if (i > 100) $clear(timer);
			i++;
		};
		var timer = boing.periodical(10);
		
	});
	
};
