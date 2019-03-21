ArrayList<Integer> l = new ArrayList<Integer>();
for (int i = 0; i < 10; ++i)
{
	l.add(i);
}
l.set(7, 77); // pos, value;
l.remove(l.size() - 1);
for (int i = l.size() - 1; i >= 0; --i)
{
	out.println(l.get(i));
}


static class myComparator implements Comparator<Integer>
{
	public int compare(Integer a, Integer b)
	{
		a %= 3; b %= 3;
		return a - b;
	}
}



ArrayList<Integer> l = new ArrayList<Integer>();
for (int i = 0; i < 10; ++i)
{
	l.add(i);
}
l.set(7, 77); // pos, value;
l.remove(l.size() - 1);
for (int i = l.size() - 1; i >= 0; --i)
{
	out.println(l.get(i));
}    	
   	
Collections.sort(l);
int pos = Collections.binarySearch(l, 1); // возвращает позицию найденого элемента
// если много одинаковых - случайный
// если не нашел, х - позиция первого большего, то вернет -x-1;
   	
Collections.sort(l, Collections.reverseOrder());
pos = Collections.binarySearch(l, 1, Collections.reverseOrder());
   	
Comparator<Integer> cmp = new myComparator();
Collections.sort(l, cmp);
   	
Integer [] x = new Integer [10];
for (int i = 0; i < 10; ++i)
{
	x[i] = i;
}
   	
int from = 3;
int to = 7;
Arrays.sort(x, from, to, cmp); // сортирует элементы 3, 4, 5, 6
Arrays.sort(x);
Arrays.sort(x, cmp);
   	
x = (Integer[]) l.toArray();
pos = Arrays.binarySearch(x, from, to, 7, cmp);
pos = Arrays.binarySearch(x, 7, cmp);


//HashSet<Integer> s = new HashSet();
TreeSet<Integer> s = new TreeSet();
s.add(5);
s.add(10);
if (s.contains(10))	System.out.print('1');
s.remove(10);
s.remove(10);
s.clear();
s.size();


//HashMap<Integer, String> m = new HashMap();
TreeMap<Integer, String> m = new TreeMap();
m.put(10, "abacaba");
System.out.println(m.get(10));
System.out.println(m.get(15)); // null
m.size();
if (m.containsKey(10)) System.out.println('2');
if (m.containsValue("abacaba")) System.out.println('3');

static MyScanner in;
static PrintWriter out;

public static void main(String args[]) throws IOException
{
	in = new MyScanner("input.txt");
	out = new PrintWriter(new FileWriter("output.txt"));
	Locale.setDefault(Locale.US);
	Locale.setDefault(Locale.US);
	new Main().Run();
	out.close();
}

public void Run() throws IOException
{
}

static class MyScanner 
{
	BufferedReader br;
	StringTokenizer st;

	MyScanner(String file) {
		try {
			br = new BufferedReader(new FileReader(new File(file)));
		} catch (FileNotFoundException e) {
			System.exit(42);
			e.printStackTrace();
		}
	}

	MyScanner() {
		try {
			br = new BufferedReader(new InputStreamReader(System.in));
		} catch (Exception e) {
			System.exit(42);
			e.printStackTrace();
		}
	}
	String nextToken() {
		while (st == null || (!st.hasMoreTokens())) {
			try {
				st = new StringTokenizer(br.readLine());
			} catch (IOException e) {
				System.exit(42);
				e.printStackTrace();
			}
		}
		return st.nextToken();
	}

	int nextInt() {
		return Integer.parseInt(nextToken());
	}

	long nextLong() {
		return Long.parseLong(nextToken());
	}
	double nextDouble() {
		return Double.parseDouble(nextToken());
	}
}
