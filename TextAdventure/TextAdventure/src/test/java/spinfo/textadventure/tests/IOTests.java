package spinfo.textadventure.tests;

import java.io.IOException;
import java.util.List;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import spinfo.textadventure.InvalidGameException;
import spinfo.textadventure.TextAdventure;
import spinfo.textadventure.data.Place;
import spinfo.textadventure.data.Player;
import spinfo.textadventure.data.World;
import spinfo.textadventure.io.IO;

public class IOTests {

	private IO io;

	@Before
	public void before() {
		io = TextAdventure.getIO();
		Assert.assertNotNull("Die Methode TextAdventure.getIO() darf nicht 'null'zurückgeben!", io);
	}

	@Test
	public void loadPlaces() throws IOException, InvalidGameException {
		List<Place> places = io.loadPlaces();
		Assert.assertNotNull("Die Methode loadPlaces() darf nicht 'null' zurückgeben!", places);
		Assert.assertTrue("Liste der Orte ist leer!", places.size() > 0);
		for (Place place : places) {
			Assert.assertNotNull("Ort hat 'null' als Namen!", place.getName());
		}
	}

	@Test
	public void loadWorld() throws IOException, InvalidGameException {
		List<Place> places = io.loadPlaces();
		World world = io.loadWorld(places);
		Assert.assertNotNull("Die Methode loadWorld() darf nicht 'null' zurückgeben!", world);
	}

	@Test
	public void loadInitialGame() throws IOException {
		Player player = io.loadGame(false);
		Assert.assertNotNull("Die Methode loadGame() darf nicht 'null' zurückgeben!", player);
	}

	@Test
	public void saveAndLoadGame() throws IOException, InvalidGameException {
		List<Place> places = io.loadPlaces();
		World world = io.loadWorld(places);
		Player player = io.loadGame(false);
		int y = player.getY();
		player.move("west", world);
		int newY = player.getY();
		Assert.assertNotSame(y, newY);
		io.saveGame(player);
		Player newPlayer = io.loadGame(true);
		Assert.assertFalse(player == newPlayer);
		Assert.assertEquals(newY, newPlayer.getY());
	}

}
