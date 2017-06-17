package spinfo.textadventure.classes;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.List;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Formatter;
import java.util.Iterator;

import spinfo.textadventure.InvalidGameException;
import spinfo.textadventure.data.Place;
import spinfo.textadventure.data.Player;
import spinfo.textadventure.data.World;
import spinfo.textadventure.games.Game;
import spinfo.textadventure.io.IO;

public class IOClass implements IO {

	private File gameDirectory;
	private String places = "places.config";
	private String world = "world.config";
	private String initial = "initial_game.config";
	private String save = "save_game.config";

	private String name = "name=";
	private String action = "action=";
	private String add = "add_conditions=";
	private String in = "in_conditions=";
	private String remove = "remove_conditions=";
	private String game = "game=";
	private File saveFile;

	@Override
	public List<Place> loadPlaces() throws InvalidGameException {
		try {
			File placeFile = new File(gameDirectory, places);

			System.out.println("PlaceDirectory: " + placeFile);

			Scanner scanner = new Scanner(placeFile);

			ArrayList<Place> placeList = new ArrayList<Place>();

			String temp = "";
			String[] tempArr = null;
			PlaceClass p = new PlaceClass();

			while (scanner.hasNextLine()) {
				temp = scanner.nextLine();
				if (temp.indexOf("=") != -1) { // found =
					if (temp.contains(name)) {
						temp = temp.replace(name, "");
						p.setName(temp);
					}
					if (temp.contains(action)) {
						temp = temp.replace(action, "");
						p.setAction(temp);
					}
					if (temp.contains(add)) {
						temp = temp.replace(add, "");
						tempArr = temp.split(",");
						p.setAddConditions(Arrays.asList(tempArr));
					}
					if (temp.contains(in)) {
						temp = temp.replace(in, "");
						tempArr = temp.split(",");
						p.setInConditions(Arrays.asList(tempArr));
					}
					if (temp.contains(remove)) {
						temp = temp.replace(remove, "");
						tempArr = temp.split(",");
						p.setRemoveConditions(Arrays.asList(tempArr));
					}
					if (temp.contains(game)) {
						temp = temp.replace(game, "");
						if (temp.contains("schnickschnackschnuck")) {
							GameClass game = new GameClass();
							game.setName((Game) game);
						} else {
							System.out.println("ERROR: Game not found.");
						}

					}
				} else {
					placeList.add(p);
					p = new PlaceClass();
				}

			}
			placeList.add(p);

			// //test output
			// Object[] ob = placeListDone.toArray();
			// int j=1;
			// for (Object value : ob) {
			//
			// System.out.println(j + " = " + value);
			// j+=1;
			// }
			// System.out.println("\n");

			scanner.close();
			return placeList;

		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}

	@Override
	public World loadWorld(List<Place> loadedPlaces) throws InvalidGameException {
		File worldFile = new File(gameDirectory, world);

		System.out.println("WorldDirectory: " + worldFile);

		WorldClass world = new WorldClass();
		ArrayList<Place> worldList = new ArrayList<Place>();
		PlaceClass p = new PlaceClass();

		String[] splitString = null;

		try {
			Scanner scanner = new Scanner(worldFile);

			String temp = "";
			String read = "";

			while (scanner.hasNextLine()) {
				temp = scanner.nextLine();
				read += temp + "|";
			}

			splitString = read.split("\\|");
			for (int i = 0; i < splitString.length; i++) {
				p.setName(splitString[i].trim());
				worldList.add(p);
				p = new PlaceClass();
			}

			scanner.close();

			// //test output
			// Object[] ob = worldList.toArray();
			// int j=1;
			// for (Object value : ob) {
			// System.out.println(j + " = " + value);
			// j+=1;
			// }
			// System.out.println("\n");

		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}

		//// //remove from loadedPlaces as test
		// for (Place placeP : new ArrayList<>(loadedPlaces)) {
		// if (test.contains((placeP.getName()))) {
		// loadedPlaces.remove(placeP);
		// }
		// }

		////// TEST Output
		// for (Place placeW : worldList) {
		// System.out.println(placeW.getName());
		// }
		// for (Place placeP : loadedPlaces) {
		// System.out.println("P: " + placeP.getName());
		// }

		int position = 0;
		for (int j = 0; j < worldList.size(); j++) {
			position = worldList.indexOf(worldList.get(j));
			Place placeW = worldList.get(j);

			Place localC = getFinalPlace(placeW, loadedPlaces);
			worldList.remove(position);
			worldList.add(position, localC);
		}

		// //save!!!!!!!!
		Place[][] worldMatrixPlace = new Place[4][3];

		Iterator<Place> iterator = (Iterator<Place>) worldList.iterator();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				if (iterator.hasNext()) {
					worldMatrixPlace[i][j] = iterator.next();
				}
			}
		}
		world.setPlaces((Place[][]) worldMatrixPlace);

		return world;
	}

	private Place getFinalPlace(Place placeW, List<Place> loadedPlaces) {

		for (Place placeP : loadedPlaces) {
			if ((placeW.getName()).equals((placeP).getName())) {
				placeW = placeP;
				return placeW;
			}
		}
		return placeW;

	}

	@Override
	public void saveGame(Player player) throws IOException {
		saveFile = new File(gameDirectory, save);

		try {
			String[] stateArr = { "x", "y", "conditions", "entered" };

			Formatter f = new Formatter(saveFile);
			f.format("%s", stateArr[0] + "=" + player.getX() + "\r\n");
			f.format("%s", stateArr[1] + "=" + player.getY() + "\r\n");
			f.format("%s", stateArr[2] + "=" + player.getConditions() + "\r\n");
			f.format("%s", stateArr[3] + "=" + player.getEnteredRooms());

			f.close();

			System.out.println("Saved game to file= " + saveFile);

		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}

	@Override
	public Player loadGame(boolean loadSaveGame) throws IOException {
		File loadFile = null;
		PlayerClass player = new PlayerClass();

		if (loadSaveGame) {
			loadFile = new File(gameDirectory, save);
		} else {
			loadFile = new File(gameDirectory, initial);
		}
		System.out.println("Loaded game from file= " + loadFile);

		try {
			Scanner scanner = new Scanner(loadFile);

			String splitString = null;
			String[] splitStringArr = null;
			String temp = "";
			String[] stateArr = { "x", "y", "conditions", "entered" };
			String state = stateArr[0];
			String last = "";

			int i = 0;
			while (scanner.hasNextLine()) {
				temp = scanner.nextLine();
				last = temp.substring(temp.length() - 1);
				if (!last.equals("=")) {
					splitString = temp.split("=")[1];

					if (state == stateArr[0]) {
						player.setX(Integer.parseInt(splitString));
						state = stateArr[++i];

					} else if (state == stateArr[1]) {
						player.setY(Integer.parseInt(splitString));
						state = stateArr[++i];

					} else if (state == stateArr[2]) {
						splitStringArr = splitString.split(",");
						player.addConditions(Arrays.asList(splitStringArr));
						state = stateArr[++i];

					} else if (state == stateArr[3]) {
						splitStringArr = splitString.split(",");
						player.setEnteredRooms(Arrays.asList(splitStringArr));
					}
				}
			}
			scanner.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		return player;
	}

	@Override
	public void setGameDirectory(File gameDirectory) {
		this.gameDirectory = gameDirectory;
		System.out.println("GameDirectory: " + gameDirectory);
	}
}