package spinfo.textadventure.classes;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import spinfo.textadventure.data.Place;
import spinfo.textadventure.data.Player;
import spinfo.textadventure.data.World;

public class PlayerClass implements Player {

	private int x = 0;
	private int y = 0;
	private List<String> getConditions = new ArrayList<String>();
	private List<String> getEnteredRooms = new ArrayList<String>();

	@Override
	public int getX() {
		return this.x;
	}

	public void setX(int x) {
		this.x = x;
	}

	@Override
	public int getY() {
		return this.y;
	}

	public void setY(int y) {
		this.y = y;
	}

	@Override
	public List<String> getConditions() {
		return this.getConditions;
	}

	@Override
	public void addConditions(List<String> conditions) {
		Iterator<String> iteratorAddConditions = conditions.iterator();
		while (iteratorAddConditions.hasNext()) {
			String temp = (String) iteratorAddConditions.next();
			if (!this.getConditions.contains(temp)) {
				this.getConditions.add(temp);
			}
		}
	}

	@Override
	public void move(String direction, World world) {
		int localX = this.x;
		int localY = this.y;
		if ("north".equals(direction)) {
			localX -= 1;
		}
		if ("south".equals(direction)) {
			localX += 1;
		}
		if ("east".equals(direction)) {
			localY += 1;
		}
		if ("west".equals(direction)) {
			localY -= 1;
		}

		try {

			Place place = world.getPlace(localX, localY);

			if (place.getName().equals("----")) {
				System.out.println("Nothing there!");
				return;
			} else if (place.canEnter(this)) {
				setX(localX);
				setY(localY);
				place.enter(this);
				if (getEnteredRooms != null) {
					if (!this.getEnteredRooms.contains(place.getName())) {
						this.getEnteredRooms.add(place.getName());
					}
				}
			}
		} catch (Exception localException) {
			System.out.println("You shall not pass!");
		}
	}

	@Override
	public boolean entered(String roomName) {
		return this.getEnteredRooms.contains(roomName);
	}

	@Override
	public List<String> getEnteredRooms() {
		return this.getEnteredRooms;
	}

	public void setEnteredRooms(List<String> getEnteredRooms) {
		this.getEnteredRooms = getEnteredRooms;
	}

}
