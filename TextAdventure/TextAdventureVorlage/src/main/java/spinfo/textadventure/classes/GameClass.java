package spinfo.textadventure.classes;

import spinfo.textadventure.games.Game;

public class GameClass implements Game {

	private String name = "";
	private String comment = "";
	private Game game;

	@Override
	public boolean play() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public String getName() {
		return this.name;
	}

	@Override
	public String getComment() {
		return this.comment;
	}

	public void setName(Game game) {
		this.game = game;
	}

}
