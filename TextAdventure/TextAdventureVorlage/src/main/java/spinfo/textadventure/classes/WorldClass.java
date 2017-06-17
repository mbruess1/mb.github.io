package spinfo.textadventure.classes;

import spinfo.textadventure.data.Place;
import spinfo.textadventure.data.World;

public class WorldClass implements World {

	private Place[][] places;
	private int maxLength = -1;

	@Override
	public void setPlaces(Place[][] places) {
		this.places = places;
	}

	@Override
	public void printMap(int playerX, int playerY) {
		// get longest place name
		for (Place[] p : places) {
			for (Place tempPlace : p) {
				if ((tempPlace != null) && (tempPlace.getName().length() > maxLength)) {
					maxLength = tempPlace.getName().length();
				}
			}
		}

		for (int i = 0; i < places.length; i++) {
			for (int j = 0; j < places[i].length; j++) {
				String localString = places[i][j].getName();
				int localLength1 = (maxLength - localString.length()) / 2;
				int localLength2 = (maxLength - localString.length()) - localLength1;

				System.out.print("|");
				for (int l = 0; l < localLength1 + 2; l++)
					System.out.print(" ");
				System.out.print(places[i][j].getName());
				if ((i == playerX) && (j == playerY)) {
					System.out.print("*");
				} else {
					System.out.print(" ");
				}
				for (int l = 0; l < localLength2 + 1; l++)
					System.out.print(" ");
			}
			System.out.print("|");
			System.out.println();
		}
	}

	@Override
	public Place getPlace(int x, int y) {
		return this.places[x][y];
	}

}
