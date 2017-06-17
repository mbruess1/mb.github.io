package spinfo.textadventure.classes;

import java.util.ArrayList;
import java.util.List;

import spinfo.textadventure.data.Place;
import spinfo.textadventure.data.Player;
import spinfo.textadventure.games.Game;

public class PlaceClass implements Place {

	private String name = "";
	private String action = "";
	private List<String> inConditions = new ArrayList<String>();
	private List<String> removeConditions = new ArrayList<String>();
	private List<String> addConditions = new ArrayList<String>();
	private Game game;

	@Override
	public String getName() {
		return this.name;
	}

	@Override
	public void setName(String name) {
		this.name = name;
	}

	@Override
	public void setAction(String action) {
		this.action = action;
	}

	@Override
	public void setInConditions(List<String> inConditions) {
		this.inConditions = inConditions;
	}

	@Override
	public void setAddConditions(List<String> addConditions) {
		this.addConditions = addConditions;
	}

	@Override
	public void setRemoveConditions(List<String> removeConditions) {
		this.removeConditions = removeConditions;
	}

	@Override
	public void setGame(Game game) {
		this.game = game;
	}

	@Override
	public boolean canEnter(Player player) {
		List<String> localList = player.getConditions();
		if (!localList.containsAll(inConditions)) {
			System.out.println("Not yet.");
			return false;
		}
		return true;
	}

	@Override
	public void enter(Player player) {
		System.out.println("You are here: " + this.getName());
		player.getConditions().removeAll(this.removeConditions);
		player.addConditions(this.addConditions);

		if ((this.action != null) && (!player.entered(this.getName()))) {
			System.out.println(this.action);
		}
	}
}
