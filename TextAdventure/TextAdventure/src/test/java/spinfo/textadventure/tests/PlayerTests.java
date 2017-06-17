package spinfo.textadventure.tests;

import java.io.IOException;
import java.util.Arrays;
import java.util.List;

import junit.framework.Assert;

import org.junit.Before;
import org.junit.Test;

import spinfo.textadventure.InvalidGameException;
import spinfo.textadventure.TextAdventure;
import spinfo.textadventure.data.Place;
import spinfo.textadventure.data.Player;
import spinfo.textadventure.data.World;
import spinfo.textadventure.io.IO;

public class PlayerTests {

	Player player;
	private World world;

	@Before
	public void before() throws IOException, InvalidGameException {
		IO io = TextAdventure.getIO();
		List<Place> places = io.loadPlaces();
		world = io.loadWorld(places);
		player = io.loadGame(false);
	}

	/**
	 * Überprüft, ob ein neuer Raum betreten werden kann und ob er zur Liste der
	 * besuchten Orte hinzugefügt wird.
	 */
	@Test
	public void testEnterRoom() {
		boolean entered = player.entered("Uni");
		Assert.assertFalse(entered);
		player.move("west", world);
		entered = player.entered("Uni");
		Assert.assertTrue(entered);
	}

	/**
	 * Überprüft, ob verhindert wird, dass der Spieler ein nicht vorhandenes
	 * Feld betritt. Das Feld rechts vom Start existiert nicht, also darf ein
	 * "move east" die Position nicht verändern.
	 */
	@Test
	public void testFailEnterMissingRoom() {
		int oldY = player.getY();
		int oldX = player.getX();
		player.move("east", world);
		Assert.assertEquals(oldY, player.getY());
		Assert.assertEquals(oldX, player.getX());
	}

	/**
	 * Überprüft, ob ein Raum betreten werden kann, wenn die Bedingungen nicht
	 * erfüllt sind.
	 */
	@Test
	public void testFailEnterConditionsNotMet() {
		player.move("west", world); // added
		player.move("east", world); // added

		player.move("north", world);
		player.move("north", world);
		player.move("north", world);
		int oldY = player.getY();
		int oldX = player.getX();
		player.move("west", world);
		Assert.assertEquals(oldY, player.getY());
		Assert.assertEquals(oldX, player.getX());
		Place place = world.getPlace(oldX, oldY);
		Assert.assertEquals("Zülpicher Straße (Nord)", place.getName());
	}

	/**
	 * Überprüft, ob ein Raum betreten werden kann, wenn die Bedingungen erfüllt
	 * sind.
	 */
	@Test
	public void testEnterConditionsMet() {
		player.move("west", world); // added
		player.move("east", world); // added

		player.move("north", world);
		player.move("north", world);
		player.move("north", world);
		int oldY = player.getY();
		int oldX = player.getX();
		player.move("west", world);
		Assert.assertEquals(oldY, player.getY());
		Assert.assertEquals(oldX, player.getX());
		Place place = world.getPlace(oldX, oldY);
		Assert.assertEquals("Zülpicher Straße (Nord)", place.getName());
		player.addConditions(Arrays.asList("not_hungry", "student_id", "from_street"));
		player.move("west", world);
		Assert.assertNotSame(oldY, player.getY());
	}

	/**
	 * Überprüft, ob der Liste der Conditions des Players neue Elemente
	 * hinzugefügt werden können.
	 */
	@Test
	public void testAddCondition() {
		List<String> test = Arrays.asList("a", "b", "c");
		Assert.assertTrue(player.getConditions().isEmpty());
		player.addConditions(test);
		Assert.assertTrue(player.getConditions().contains("a"));
		Assert.assertTrue(player.getConditions().contains("b"));
		Assert.assertTrue(player.getConditions().contains("c"));
	}

}
