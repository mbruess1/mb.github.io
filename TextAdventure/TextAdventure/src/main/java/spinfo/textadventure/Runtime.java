package spinfo.textadventure;

import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

import spinfo.textadventure.data.Place;
import spinfo.textadventure.data.Player;
import spinfo.textadventure.data.World;
import spinfo.textadventure.io.IO;

/**
 * Diese Klasse implementiert die Laufzeitumgebung des Spiels und kümmert sich
 * darum, die Benutzereingaben auf der Konsole zu interpretieren. Je nach
 * Eingabe wird eine der folgenden Methoden aufgerufen:
 * 
 * <ul>
 * <li>IO.loadGame()</li>
 * <li>IO.saveGame()</li>
 * <li>Player.move()</li>
 * <li>World.printMap()</li>
 * </ul>
 * 
 */
public class Runtime {

	private Player player;
	private World world;
	private IO io;

	public void play() {
		while (true) {
			execNext();
		}
	}

	private void execNext() {
		Map<String, Integer> keys = new HashMap<String, Integer>();
		keys.put("go", 1);
		keys.put("map", 2);
		keys.put("save", 3);
		keys.put("load", 4);
		keys.put("exit", 5);
		Scanner s = new Scanner(System.in);
		world.printMap(player.getX(), player.getY());
		while (s.hasNextLine()) {
			String line = s.nextLine();
			String[] toks = line.split(" ");
			Integer i = keys.get(toks[0]);
			if (i == null)
				i = -1;
			executeCommand(toks, i);
		}
		s.close();
	}

	protected void executeCommand(String[] tokens, int command) {
		switch (command) {
		case 1:
			if (tokens.length == 2) {
				String direction = tokens[1];
				movePlayer(direction);
			} else
				System.out.println("Wohin willst Du?");
			break;
		case 2:
			world.printMap(player.getX(), player.getY());
			break;
		case 3:
			try {
				saveGame();
			} catch (IOException e) {
				e.printStackTrace();
			}
			break;
		case 4:
			try {
				loadGame();
			} catch (IOException e) {
				e.printStackTrace();
			}
			break;
		case 5:
			System.exit(0);
			break;
		default:
			System.out.println("Ich verstehe Dich nicht.");
		}
	}

	public void loadGame() throws IOException {
		player = io.loadGame(true);
	}

	public void saveGame() throws IOException {
		io.saveGame(player);
	}

	public void movePlayer(String direction) {
		player.move(direction, world);
	}

	public Player getPlayer() {
		return player;
	}

	public World getWorld() {
		return world;
	}

	public void initialize(IO io) throws InvalidGameException {
		this.io = io;
		try {
			List<Place> places = io.loadPlaces();

			// //test output
			// System.out.println("\n");
			// int j=1;
			// for (Place value : places) {
			//
			// System.out.println(j + " = " + value.getName());
			// j+=1;
			// }
			// System.out.println("\n");
			// System.out.println("\n");

			world = io.loadWorld(places);
			player = io.loadGame(false);

//			player.move(world.getPlace(player.getX(), player.getY()).getName(), world); //own

		} catch (IOException e) {
			throw new InvalidGameException("Fehler beim Laden des Spiels!", e);
		}
	}
}
