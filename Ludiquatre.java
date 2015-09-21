import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

/**
 * Versie van een vier-op-een-rij computertegenstander
 * 
 * @author Ludo Pulles
 */
public class Ludiquatre {

	private static MinimaxNode huidigeNode;
	private static boolean isWit = false;

	private static final int BREEDTE = 7, HOOGTE = 6;
	/** de kleuren die in het bord komen. */
	private static final byte LEEG = 0, IK = 1, HIJ = 2;

	/**
	 * Dit zijn alle mogelijkheden dat er vier-op-een-rij kan voorkomen.
	 * {@link DIAGONAAL45} gaat van linksonder naar rechtsboven,
	 * {@link DIAGONAAL135} gaat van linksboven naar rechtsonder
	 */
	private static final int HORIZONTAAL = 0, VERTICAAL = 1, DIAGONAAL45 = 2,
			DIAGONAAL135 = 3;
	/** {@link Integer#MAX_VALUE} = 2.147.483.648 */
	private static final int[] RATINGS = new int[] { 1, 100, 10000, 1000000 };

	private static class MinimaxNode {

		private byte kleur;
		private byte[][] bord;
		private Rating rating;
		private MinimaxNode[] nodes = null;

		/** kleur = de speler die de zet 'nu' moet doen */
		private MinimaxNode(byte[][] oudBord, byte kleur, int kolom,
				int stappenVooruit) throws IllegalStateException {
			this(doeZet(oudBord, kleur, kolom), kleur, stappenVooruit);
		}

		/** kleur = de speler die de laatste zet heeft gezet */
		private MinimaxNode(byte[][] bord, byte kleur, int stappenVooruit) {
			this.bord = bord;
			this.kleur = kleur;
			this.rating = new Rating(bord);
			denkVooruit(stappenVooruit);
		}

		private byte getNodeKleur() {
			return kleur == IK ? HIJ : (kleur == HIJ ? IK : LEEG);
		}

		/** dit kiest de node met de hoogste rating */
		private int besteZet(boolean ik) {
			if (nodes == null) {
				return -1;
			}
			float hoogsteRating = 0;
			int index = -1;
			for (int i = 0; i < nodes.length; i++) {
				if (nodes[i] != null) {
					float rating = nodes[i].rating.rating;
					if (index == -1
							|| (ik ? rating > hoogsteRating
									: rating < hoogsteRating)) {
						hoogsteRating = rating;
						index = i;
					}
				}
			}
			return index;
		}

		/** hoeveel stappen deze node vooruit moet denken dmv recursie */
		private void denkVooruit(int stappenVooruit) {
			byte nodeKleur = getNodeKleur();
			if (stappenVooruit > 0 && rating.winnaar == LEEG) {
				// de zetten die de tegenstander verplicht moet doen!
				if (rating.winKansen != null && rating.winKansen.length > 0) {
					int[] winKansen = rating.winKansen;
					// verplichte zetten, waardoor er maar 1 mogelijkheid is
					// voor de nodes, omdat die stap wel moet worden ondernomen,
					// omdat er anders niet gewonnen wordt
					// er zijn meerdere verplichte zetten voor de andere

					// reset de nodes
					this.nodes = new MinimaxNode[7];
					for (int i = 0; i < winKansen.length; i++) {
						// alleen die win kansen zijn initialiseren

						// we laten de waarde van stappenVooruit niet 1 afnemen
						// zoals normaal, omdat het hier maar een klein aantal
						// nodes bevat.
						this.nodes[winKansen[i]] = new MinimaxNode(bord,
								nodeKleur, winKansen[i], stappenVooruit);
					}
					// de beste van de verplichte zetten zoeken...
					if (winKansen.length == 1) {
						this.rating = this.nodes[winKansen[0]].rating;
					} else {
						int besteZet = besteZet(nodeKleur == IK);
						for (int i = 0; i < winKansen.length; i++) {
							if (winKansen[i] != besteZet) {
								// de rest 'verwijderen'
								this.nodes[winKansen[i]] = null;
							}
						}
						this.rating = this.nodes[besteZet].rating;
					}
				} else {
					this.nodes = new MinimaxNode[BREEDTE];
					for (int i = 0; i < BREEDTE; i++) {
						try {
							nodes[i] = new MinimaxNode(bord, nodeKleur, i,
									stappenVooruit - 1);
						} catch (IllegalStateException e) {
						}
					}
					this.rating = new Rating(nodes);
				}
			}
		}

		private MinimaxNode initNode(int index) {
			if (nodes == null) {
				nodes = new MinimaxNode[BREEDTE];
			}
			byte nodeKleur = getNodeKleur();
			if (nodes[index] == null) {
				try {
					nodes[index] = new MinimaxNode(bord, nodeKleur, index, 0);
				} catch (IllegalStateException e) {
				}
			}
			return nodes[index];
		}

		private void initNodes() {
			if (nodes == null) {
				nodes = new MinimaxNode[BREEDTE];
			}
			byte nodeKleur = getNodeKleur();
			for (int i = 0; i < BREEDTE; i++) {
				if (nodes[i] == null) {
					try {
						nodes[i] = new MinimaxNode(bord, nodeKleur, i, 0);
					} catch (IllegalStateException e) {
					}
				}
			}
		}

	}

	private static class Rating {

		private float rating = 0;
		private byte winnaar = LEEG;

		private int[] winKansen = null;

		private Rating(byte[][] bord) {
			for (int y = 0; y < bord.length; y++) {
				for (int x = 0; x < bord[y].length; x++) {
					boolean horizontaalKan = x + 3 < bord[y].length;
					boolean verticaalKan = y + 3 < bord.length;
					if (horizontaalKan) {
						rate(bord, x, y, HORIZONTAAL);
					}
					if (verticaalKan) {
						rate(bord, x, y, VERTICAAL);
						if (horizontaalKan) {
							rate(bord, x, y, DIAGONAAL45);
							rate(bord, x, y, DIAGONAAL135);
						}
					}
					if (winnaar != LEEG) {
						rating = (winnaar == IK ? 100 : -100) * RATINGS[3];
						this.winKansen = null;
						return;
					}
				}
			}
		}

		private void addRating(int i, boolean ik) {
			if (ik) {
				this.rating += i;
			} else {
				this.rating -= i;
			}
		}

		private Rating(MinimaxNode[] nodes) {
			// de rating is het gemiddelde van de nodes, die NIET NULL is
			double ratingGem = 0;
			// uit hoeveel getallen ratingGem het gemiddelde is genomen
			int n = 0;
			for (int i = 0; i < nodes.length; i++) {
				if (nodes[i] != null) {
					ratingGem += nodes[i].rating.rating;
					n++;
				}
			}
			this.rating = (float) ratingGem / n;
			this.winnaar = LEEG;
		}

		private void rate(byte[][] bord, int x, int y, int richting) {
			int[] points = new int[8];
			int aantalIK = 0, aantalHIJ = 0;
			for (int i = 0; i < 4; i++) {
				// x
				points[i * 2] = (richting == VERTICAAL ? x : x + i);
				// y
				points[i * 2 + 1] = (richting == DIAGONAAL135 ? y + 3 - i
						: (richting == HORIZONTAAL ? y : y + i));
				if (bord[points[i * 2 + 1]][points[i * 2]] == IK) {
					aantalIK++;
				} else if (bord[points[i * 2 + 1]][points[i * 2]] == HIJ) {
					aantalHIJ++;
				}
			}

			if (aantalIK == 4) {
				this.winnaar = IK;
			} else if (aantalHIJ == 4) {
				this.winnaar = HIJ;
			} else if ((aantalIK == 3 && aantalHIJ == 0)
					|| (aantalHIJ == 3 && aantalIK == 0)) {
				for (int i = 0; i < 4; i++) {
					if (bord[points[i * 2 + 1]][points[i * 2]] == LEEG) {
						boolean ik = (aantalIK == 3);
						int missingX = points[i * 2], missingY = points[i * 2 + 1];
						if (missingY == 0
								|| bord[missingY - 1][missingX] != LEEG) {
							addVerplichteZet(missingX);
							addRating(RATINGS[2], ik);
						} else if (((isWit == ik) && (y & 1) == 0)
								|| ((isWit != ik) && (y & 1) == 1)) {
							addRating(10 * RATINGS[2], ik);
						} else {
							addRating(2 * RATINGS[2], ik);
						}
						break;
					}
				}
			} else if (aantalIK != 0 && aantalHIJ == 0) {
				// 'ik' heeft een rij :). De rating is positief
				addRating(RATINGS[aantalIK - 1], true);
			}
		}

		private void addVerplichteZet(int x) {
			if (winKansen == null) {
				winKansen = new int[] { x };
			} else {
				// de oude grootte van de array maar ook de index van het nieuwe
				// element
				final int len = winKansen.length;
				for (int i = 0; i < len; i++) {
					if (winKansen[i] == x) {
						return;
					}
				}
				// unieke kolom
				int[] newarray = new int[len + 1];
				System.arraycopy(winKansen, 0, newarray, 0, len);
				newarray[len] = x;
				winKansen = newarray;
			}
		}

		@Override
		public String toString() {
			String str = "(r: " + rating;
			if (winnaar != LEEG) {
				str += ",w: " + winnaar;
			}
			if (winKansen != null) {
				str += ",z: " + Arrays.toString(winKansen);
			}
			return str + ")";
		}

	}

	/**
	 * doet een zet op het speelbord, en geeft dit bord terug. Het bord wordt
	 * niet aangepast, maar er wordt een nieuw speelbord aangemaakt
	 * 
	 * @return het nieuwe bord
	 */
	private static byte[][] doeZet(byte[][] oudBord, byte kleur, int kolom)
			throws IllegalStateException {
		byte[][] bord = new byte[HOOGTE][BREEDTE];
		for (int y = 0; y < HOOGTE; y++) {
			System.arraycopy(oudBord[y], 0, bord[y], 0, BREEDTE);
		}
		for (int y = 0; y < HOOGTE; y++) {
			if (bord[y][kolom] == LEEG) {
				bord[y][kolom] = kleur;
				return bord;
			}
		}
		// het bord is in deze kolom vol
		throw new IllegalStateException("Kolom " + (kolom + 1) + " is vol\n");
	}

	private static int stappenVooruit() {
		long tijd_bezig = getTijdBezig();
		// System.err.print("tijdBezig=" + tijd_bezig + ",stappenVooruit=");
		if (tijd_bezig > 3500) {
//			System.err.println(4);
			return 4;
		}
//		System.err.println(5);
		return 5;
	}

	private static long tijdBezig = 0;
	private static long beginRonde = 0;

	private static long getTijdBezig() {
		return tijdBezig + (System.currentTimeMillis() - beginRonde);
	}

	private static void updateNodes(byte[][] bord, int zet, boolean hijZette) {
		if (hijZette) {
			if (huidigeNode == null) {
				// (waarschijnlijk) de eerste keer
				huidigeNode = new MinimaxNode(bord, HIJ, stappenVooruit());
			} else {
				if (huidigeNode.nodes == null || huidigeNode.nodes[zet] == null
						&& huidigeNode.initNode(zet) == null) {
					// de zet kan nu niet op het bord worden gemaakt, dus
					// passen we het bord niet aan.
					huidigeNode = new MinimaxNode(bord, IK, stappenVooruit());
				} else {
					huidigeNode = huidigeNode.nodes[zet];
					huidigeNode.denkVooruit(stappenVooruit());
				}
			}
			huidigeNode.initNodes();
		} else {
			if (huidigeNode == null || huidigeNode.nodes == null) {
				huidigeNode = null;
			} else {
				huidigeNode = huidigeNode.nodes[zet];
			}
		}
	}

	public static void main(String[] args) throws IOException {
		// 435644536335625262
		// luistert naar zetten van de tegenstander
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		// [0][0] = links onderin, [5][6] = rechts bovenin
		byte[][] bord = new byte[HOOGTE][BREEDTE];

		// firsterror
//		System.err.println("R Ludiquatre");
//		System.err.flush();

		String zet;
		while ((zet = in.readLine()) != null) {
			if (zet.length() == 0) {
				// soms hebben we gewoon niets te zeggen
				continue;
			} else if (zet.equalsIgnoreCase("quit")) {
				// tot ziens!
				break;
			} else if (zet.equalsIgnoreCase("start")) {
				// Ik mag beginnen. We doen het midden, dat is het chillst
				isWit = true;
				int mijnZet = 3;
				for (int y = 0; y < HOOGTE; y++) {
					if (bord[y][mijnZet] == LEEG) {
						bord[y][mijnZet] = IK;
						break;
					}
				}
//				System.err.println(mijnZet + 1);
//				System.err.flush();
				System.out.println(mijnZet + 1);
				System.out.flush();
			} else if (zet.length() != 1 || zet.charAt(0) < '1'
					|| zet.charAt(0) > '7') {
//				System.err.println("Invalid input '" + zet + "'!");
//				System.err.flush();
				// wie de bal kaatst, kan hem terug verwachten ;)
				System.out.println(zet);
				System.out.flush();
			} else {
				// een getal tussen de 1 en de 7 die de tegenstander heeft
				// gespeeld
				beginRonde = System.currentTimeMillis();
				// zijn zet
				int zijnZet = Integer.parseInt(zet.trim()) - 1;
				for (int y = 0; y < HOOGTE; y++) {
					if (bord[y][zijnZet] == LEEG) {
						bord[y][zijnZet] = HIJ;
						break;
					}
				}
//				print(bord);
				updateNodes(bord, zijnZet, true);
				// mijn zet
				int mijnZet = huidigeNode.besteZet(true);
				if (mijnZet == -1) {
					mijnZet = 3;
				}
				for (int y = 0; y < HOOGTE; y++) {
					if (bord[y][mijnZet] == LEEG) {
						bord[y][mijnZet] = IK;
						break;
					}
				}
				updateNodes(bord, mijnZet, false);

				long tijdBeginZet = System.currentTimeMillis() - beginRonde;
				tijdBezig += tijdBeginZet;

//				print(huidigeNode);
//				System.err.println("tijd bezig: " + tijdBeginZet);
//				print(bord);
//				System.err.println(mijnZet + 1);
//				System.err.flush();

				System.out.println(mijnZet + 1);
				System.out.flush();
			}
		}
//		System.err.println("tijd: " + tijdBezig);
//		System.err.flush();
	}

	/*
	private static void print(byte[][] bord) {
		StringBuilder sb = new StringBuilder(BREEDTE * HOOGTE);
		for (int y = bord.length - 1; y >= 0; y--) {
			for (int x = 0; x < bord[y].length; x++) {
				if (x != 0) {
					sb.append("|");
				}
				sb.append(bord[y][x]);
			}
			sb.append('\n');
		}
		System.err.println(sb);
	}

	private static void print(MinimaxNode node) {
		if (node == null || node.nodes == null) {
			System.err.println("null");
			return;
		}
		for (int i = 0; i < node.nodes.length; i++) {
			MinimaxNode nodeN = node.nodes[i];
			System.err.println((i + 1) + ": "
					+ (nodeN == null ? "null" : nodeN.rating));
		}
	}
	*/
}