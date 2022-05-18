public class No {
    public int n;
    public boolean folha;
    public int[] chave = new int[2*BTree.t-1];
    public No[] filhos = new No[2*BTree.t];

    public No(int n, boolean folha){
        this.n = n;
        this.folha = folha;
    }

    public No(){

    }

}
