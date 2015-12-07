	var _mapList;
	var _mapID;
	var _playerCount;
	var _availablePlayers = [];
	var colors = ['white', 'black', 'red', 'green', 'blue', 'yellow', 'orange', 'brown', 'purple', 'cyan', 'magenta'];
	var available_colors = [];
	
	function init()
	{
		window.addEventListener('keydown', userInput);
	}
	
	function changeScreen(screen)
	{
		var screens = document.getElementsByClassName('screen');
		for(var i = 0; i < screens.length; ++i)
			screens[i].classList.remove('active');
		document.getElementById(screen).classList.add('active');
	}
	
	function initGameSetup()
	{
		for (var i = 0; i < colors.length; i++)
			available_colors.push(colors[i]);
		createMapList();
	}
	
	function createMapList()
	{
		var tbody = document.getElementById('mapList');
		while (tbody.hasChildNodes()) {   
			tbody.removeChild(tbody.firstChild);
		}
		_mapList = getMaps();
		for (var i = 0; i < _mapList.length; i++)
		{
			var row = document.createElement('tr');
			row.id = i;
			row.onclick = function(){setSelectedMap(this.id);};
			var cell = document.createElement('td');
			cell.appendChild(document.createTextNode(_mapList[i].name));
			row.appendChild(cell);
			cell = document.createElement('td');
			cell.appendChild(document.createTextNode(_mapList[i].playerPositions.length));
			row.appendChild(cell);
			tbody.appendChild(row);
		}
		setSelectedMap(0);
	}
	
	function userInput(event)
	{
		if (event.keyCode == 40)
		{
			if (_mapID < (_mapList.length - 1))
				setSelectedMap(++_mapID);
		}
		else if (event.keyCode == 38)
		{	
			if (_mapID > 0)
				setSelectedMap(--_mapID);
		}
		else if (event.keyCode == 27)
			changeScreen('mainMenu');
	}
	
	function setSelectedMap(i)
	{
		var tbody = document.getElementById('mapList');
		for (var j = 0; j < tbody.rows.length; j++)
		{
			tbody.rows[j].cells[0].style.background = '#1f2024';
			tbody.rows[j].cells[1].style.background = '#1f2024';
		}
		tbody.rows[i].cells[0].style.background = '#5D5F6B';
		tbody.rows[i].cells[1].style.background = '#5D5F6B';
		updateMapinfos(i);
		setMap(i);
		_mapID = i;
	}
	
	function updateMapinfos(i)
	{
		document.getElementById("mapName").innerHTML = _mapList[i].name;
		document.getElementById("mapImage").src = _mapList[i].image;
		document.getElementById("description").innerHTML = _mapList[i].description;
		_playerCount = _mapList[i].playerPositions.length;
		createPosButtons();
		_availablePlayers = [];
		for (i = 1; i <= _playerCount; i++)
		{
			_availablePlayers.push(i);
		}
		updatePlayerList();
	}
	
	function createKISelect()
	{
		var sel = document.createElement('select');
		sel.id = 'ki';
		sel.style.background = '#5D5F6B';
		var opt = document.createElement('option');
		opt.value = 'open';
		opt.innerHTML = '-open-';
		sel.appendChild(opt);
		opt = document.createElement('option');
		opt.value = 'closed';
		opt.innerHTML = '-closed-';
		sel.appendChild(opt);
		kis = getKIs();
		for (var i = 0; i < kis.length; i++)
		{
			opt = document.createElement('option');
			opt.value = kis[i];
			opt.innerHTML = kis[i];
			sel.appendChild(opt);
		}
		return sel;
	}
	
	function createFactionSelect()
	{
		var sel = document.createElement('select');
		sel.id = 'faction';
		sel.style.background = '#5D5F6B';
		var opt = document.createElement('option');
		opt.value = 'Random';
		opt.innerHTML = 'Random';
		sel.appendChild(opt);
		opt = document.createElement('option');
		opt.value = 'Observer';
		opt.innerHTML = 'Observer';
		sel.appendChild(opt);
		factions = getFactions();
		for (var i = 0; i < factions.length; i++)
		{
			opt = document.createElement('option');
			opt.value = factions[i];
			opt.innerHTML = factions[i];
			sel.appendChild(opt);
		}
		return sel;
	}
	
	function createTeamSelect()
	{
		var sel = document.createElement('select');
		sel.id = 'team';
		sel.style.background = '#5D5F6B';
		var opt = document.createElement('option');
		opt.value = '-';
		opt.innerHTML = '-';
		sel.appendChild(opt);
		for (var i=1; i <= _playerCount; i++)
		{
			opt = document.createElement('option');
			opt.value = i;
			opt.innerHTML = i;
			sel.appendChild(opt);
		}
		return sel;
	}
	
	function createColorSelect()
	{
		var sel = document.createElement('select');
		sel.id = 'color';
		for (var i = 0; i < available_colors.length; i++)
		{
			var opt = document.createElement('option');
			opt.value = available_colors[i];
			opt.style.background = available_colors[i];
			sel.appendChild(opt);
		}
		return sel;
	}
	
	function updatePlayerList()
	{
		var table = document.getElementById('playerList');
		var delta = _playerCount - (table.rows.length); //the head row is always there
		if (delta == 0) return;
		else if (delta > 0)
		{
			//update the team selections of the existing rows
			for (var i = 0; i < table.rows.length; i++)
			{
				table.rows[i].cells[2].replaceChild(createTeamSelect(), table.rows[i].cells[2].childNodes[0]);
			}
			
			var tbody = document.getElementById('playerList');
			for(var i = 0; i < delta; i++) 
			{
				var row = document.createElement('tr');
				row.onchange = 'updatePlayerInfo(this);';
				var cell = document.createElement('td');
				if (table.rows.length == 0) {
					cell.appendChild(document.createTextNode(getPlayerName()));
				} else {
					cell.appendChild(createKISelect());
				}
				row.appendChild(cell);
				
				cell = document.createElement('td');
				cell.appendChild(createFactionSelect());
				row.appendChild(cell);
				
				cell = document.createElement('td');
				cell.appendChild(createTeamSelect());
				row.appendChild(cell);
				
				cell = document.createElement('td');
				cell.appendChild(createColorSelect());
				row.appendChild(cell);
				
				tbody.appendChild(row);
			}
		}
		else
		{
			for (var i = delta; i < 0; i++)
			{
				table.deleteRow(table.rows.length - 1);
			}
			
			//update the team selections of the existing rows
			for (var i = 0; i < table.rows.length; i++)
			{
				table.rows[i].cells[2].replaceChild(createTeamSelect(), table.rows[i].cells[2].childNodes[0]);
			}
		}
	}
	
	function updatePlayerInfo(row) //implement in engine
	{
		alert("update player info");
	    /*
		var x = row.cells;
		var name = x[0].innerHTML;
		alert(x[1].);
		var factionSel = x[1].getElementById("faction");
		alert("test");
		var faction = factionSel.options[factionSel.selectedIndex].value;
		var teamSel = x[2].getElementById("team");
		var team =  teamSel.options[teamSel.selectedIndex].value;
		var colSel = x[3].getElementById("color");
		var color =  colSel.options[colSel.selectedIndex].value;
		
		alert(name);
		alert(faction);
		alert(team);
		alert(color);

		//updatePlayer(name, faction, team, color); implement in engine
		*/
	}
	
	function createPosButtons()
	{
		var div = document.getElementById('mapImageContainer');
		while (div.childNodes.length > 1)
		{
			if (div.firstChild.id == "mapImage") div.appendChild(div.firstChild);
			div.removeChild(div.firstChild);
		}
		var width = document.getElementById('mapImage').width;
		var height = document.getElementById('mapImage').height;
		if (! height) {
			setTimeout(createPosButtons, 1);
			return;
		}
		var map = _mapList[_mapID];
		for (var i = 0; i < _playerCount; i++)
		{
			var span = document.createElement('span');
			span.className = "round_button";
			div.appendChild(span);
			span.onclick = function(){countUp(this);};
			span.style.top = map.playerPositions[i].y / map.size.height * height - span.clientHeight;
			span.style.left = map.playerPositions[i].x / map.size.width * width - span.clientWidth;
		}
	}
	
	function contains(a, obj)
	{
		for(var i = 0; i < a.length; i++)
		{
			if(a[i] == obj) return true;
		}
		return false;
	}
	
	function countUp(button)
	{
		var num = Number(button.innerHTML);
		if (button.innerHTML == ' ')
		{
			button.innerHTML = _availablePlayers[0];
			_availablePlayers.splice(0, 1);
		}
		else if (num == _playerCount || _availablePlayers.length == 0) 
		{
			button.innerHTML =  ' ';
			_availablePlayers.push(num);
		}
		else
		{
			var n = num;
			do {
				n += 1;
				if (n > _playerCount)
				{
					button.innerHTML =  ' ';
					_availablePlayers.push(num);
					return;
				}
			} while (!contains(_availablePlayers, n));
			button.innerHTML = n;
			var index = _availablePlayers.indexOf(n);
			_availablePlayers.splice(index, 1);
			if (num > 0)
				_availablePlayers.push(num);
		}
	}
	
	
	
	
	//functions below must be implemented in engine
	
	function getKIs()
	{
		return ['Easy', 'Medium', 'Hard', 'Brutal'];
	}
	
	function getFactions()
	{
		return ['Gondor', 'Rohan', 'Isengard', 'Mordor'];
	}
	
	function getPlayerName()
	{
		return 'Tarcontar';
	}
	
	function getMaps()
	{
		return [
			{
				name: 'Lindon', 
				playerPositions: [{x:100, y:100}, {x:300, y:100}, {x:300, y:300}], 
				image:'mapsample.png', 
				description:'descLindon', 
				size: {width:400, height:400}
			},
			{
				name: 'Nanduhirion',
				playerPositions: [{x:100, y:100}, {x:150, y:30}, {x:100, y:40}, {x:200, y:50}, {x:200, y:200}, {x:30, y:300}],
				image:'mapsample2.png', 
				description:'descNandu', 
				size: {width:400, height:400}
			},
			{
				name: 'Arthedain',
				playerPositions: [{x:10, y:10}, {x:10, y:1}, {x:10, y:4}, {x:20, y:5}, {x:20, y:20}, {x:3, y:30}, {x:30, y:20}, {x:15, y:30}, {x:20, y:5}, {x:20, y:20}, {x:3, y:30}, {x:30, y:20}, {x:15, y:30} ],
				image:'mapsample3.png', 
				description:'descArthedain', 
				size: {width:40, height:30}
			}
		];
	}
	
	function setMap(id)
	{
	}