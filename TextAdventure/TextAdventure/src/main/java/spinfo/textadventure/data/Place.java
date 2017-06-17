package spinfo.textadventure.data;

import java.util.List;

import spinfo.textadventure.games.Game;

/**
 * Beschreibt einen Ort im Spiel.
 *
 */
public interface Place {

	/**
	 * Gibt den Namen des Ortes zurück
	 */
	public String getName();

	/**
	 * Setzt den Namen des Ortes
	 */
	public void setName(String name);

	/**
	 * Setzt die "Aktion" des Ortes, d.h. den
	 * String, der ausgegeben wird, wenn der Ort
	 * betreten wird.
	 * @param action
	 */
	public void setAction(String action);

	/**
	 * Setzt die Eingangs-Bedingungen, die erfüllt
	 * sein müssen, damit der Ort betreten werden darf.
	 */
	public void setInConditions(List<String> inConditions);

	/**
	 * Setzt die Bedingungen, die hinzugefügt werden,
	 * wenn der Spieler den Ort betritt.
	 * @param addConditions
	 */
	public void setAddConditions(List<String> addConditions);

	/**
	 * Setzt die Bedingungen, die entfernt werden,
	 * wenn der Spieler den Ort betritt.
	 * @param removeConditions
	 */
	public void setRemoveConditions(List<String> removeConditions);

	/**
	 * Setzt das Mini-Spiel, das bei erstmaligem Betreten
	 * des Raums gespielt werden muss.
	 * @param game
	 */
	public void setGame(Game game);

	/**
	 * Gibt true zurück, wenn der Raum bereits betreten wurde
	 * oder wenn die Eingangs-Bedingungen erfüllt sind. In allen
	 * anderen Fällen muss false zurückgegeben werden.
	 * @param player
	 * @return
	 */
	public boolean canEnter(Player player);

	
	public void enter(Player player);

}
