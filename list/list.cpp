
namespace lasd {

/* ************************************************************************** */

  //Node

  //Costruttori specifici
  template <typename Data>
  List<Data>::Node::Node(const Data& dato){
    element = dato;
  }

  template <typename Data>
  List<Data>::Node::Node(Data&& dato) noexcept{

    std::swap(dato, element);

  }

  // Copy constructor

  template <typename Data>
  List<Data>::Node::Node(const Node& nodoDaCopiare){

    element = nodoDaCopiare.element;
    next = nodoDaCopiare.next;

  }

  // Move constructor

  template <typename Data>
  List<Data>::Node::Node(Node&& nodoDaCopiare) noexcept {

    std::swap(element, nodoDaCopiare.element);
    std::swap(next, nodoDaCopiare.next);

  }

  // Distruttore

  template <typename Data>
  List<Data>::Node::~Node(){
    delete next;
  }

  // Operatori di confronto

  template <typename Data>
  bool List<Data>::Node::operator==(const Node& nodo) const noexcept {

    if (element == nodo.element){

      if (next == nullptr && nodo.next == nullptr) return true;
      else {

        if (next != nullptr && nodo.next != nullptr){
          if (*next == *(nodo.next)) return true;
          else return false;
        }
        else return false;

      }

    }
    else return false;

  }

  template <typename Data>
  bool List<Data>::Node::operator!=(const Node& nodo) const noexcept{
    return !(*this == nodo);
  }

/* ************************************************************************** */

  // List

  //Costruttore specifico

  template <typename Data>
  List<Data>::List(const LinearContainer<Data>& containerIniziale){

    for (ulong i = 0; i < containerIniziale.Size(); i++){

      InsertAtBack(containerIniziale[i]);

    }

  }

/* ************************************************************************ */

  //Copy constructor

  template<typename Data>
  List<Data>::List(const List<Data>& lista) {

    Node* curr = lista.head;

    while (curr != nullptr){

      InsertAtBack(curr->element);
      curr = curr->next;

    }

  }

  //Move Constructor

  template<typename Data>
  List<Data>::List(List<Data>&& lista) noexcept {

    std::swap(lista.head, head);
    std::swap(lista.tail, tail);
    std::swap(lista.size, size);

  }

  /* ************************************************************************ */

  // Distruttore

  template<typename Data>
  List<Data>::~List() {

    delete head;

  }

  /* ************************************************************************ */

  // Copy assignment

  template<typename Data>
  List<Data>& List<Data>::operator=(const List<Data>& lista){

    Clear();

    Node* curr = lista.head;

    while (curr != nullptr){

      InsertAtBack(curr->element);
      curr = curr->next;

    }

    return *this;

  }

  // Move assignment

  template<typename Data>
  List<Data>& List<Data>::operator=(List<Data>&& lista) noexcept {

    std::swap(lista.head, head);
    std::swap(lista.tail, tail);
    std::swap(lista.size, size);

    return *this;

  }

  /* ************************************************************************ */

  //Operatori di confronto

  template<typename Data>
  bool List<Data>::operator==(const List<Data>& lista) const noexcept {

    if (size == lista.size) {

      if (size == 0) return true;
      else return *head == *(lista.head);

    }
    else return false;

  }

  template<typename Data>
  bool List<Data>::operator!=(const List<Data>& lista) const noexcept {
    return !(lista==*this);
  }

/* ************************************************************************ */

  //Specific member functions

  template<typename Data>
  void List<Data>::InsertAtFront(const Data& dato) {

    Node* nodo = new Node(dato);

    if (size == 0) {
      head = nodo;
      tail = head;
    }

    else {
      nodo->next = head;
      head = nodo;
    }

    size++;

  }

  template<typename Data>
  void List<Data>::InsertAtFront(Data&& dato) {

    Node* nodo = new Node(std::move(dato));

    if (size == 0) {
      head = nodo;
      tail = head;
    }

    else {
      nodo->next = head;
      head = nodo;
    }

    size++;

  }

  template<typename Data>
  void List<Data>::RemoveFromFront() {

    if (size==0) throw std::length_error("Tentata rimozione da lista vuota.");

    else {

      Node* temp = head;
      head = head->next;
      temp->next = nullptr;
      delete temp;
      size--;

      if (size == 0) tail = nullptr;

    }

  }

  template<typename Data>
  Data List<Data>::FrontNRemove() {

    if (size==0) throw std::length_error("Tentata rimozione da lista vuota.");

    else {

      Node* temp = head;
      head = temp->next;
      Data elem = temp->element;
      temp->next = nullptr;
      delete temp;
      size--;
      return elem;

      if (size == 0) tail = nullptr;

    }


  }

  template<typename Data>
  void List<Data>::InsertAtBack(const Data& dato) {

    Node* nodo = new Node(dato);

    if (size == 0) {
      head = nodo;
      tail = head;
    }

    else {
      tail->next = nodo;
      tail = nodo;
    }

    size++;

  }

  template<typename Data>
  void List<Data>::InsertAtBack(Data&& dato) {

    Node* nodo = new Node(std::move(dato));

    if (size == 0) {
      head = nodo;
      tail = head;
    }

    else {
      tail->next = nodo;
      tail = nodo;
    }

    size++;

  }

/* ************************************************************************ */

  // Ereditate da Container

  template<typename Data>
  void List<Data>::Clear() {

    delete head;
    head = nullptr;
    tail = nullptr;
    size = 0;

  }

/* ************************************************************************ */

// Specific member functions (inherited from LinearContainer)

  template<typename Data>
  Data& List<Data>::Front() const {

    if (size == 0) throw std::length_error ("Tentato accesso a una lista vuota.");

    else return head->element;

  }

  template<typename Data>
  Data& List<Data>::Back() const {

    if (size == 0) throw std::length_error ("Tentato accesso a una lista vuota.");

    else return tail->element;

  }

  template<typename Data>
  Data& List<Data>::operator[](const ulong indice) const {

    if (indice < size) {

      Node* curr = head;

      for (int i = 0; i < indice; i++)
        curr = curr->next;

      return curr->element;

    }
    else  throw std::out_of_range ("Tentato accesso all'indice " + std::to_string(indice)
      + " di una lista di taglia " + std::to_string(size));

  }

/* ************************************************************************ */


  // Specific member functions (inherited from MappableContainer)

  template<typename Data>
  void List<Data>::Map(MapFunctor functor, void* parametro) {

    MapPreOrder(functor, parametro);

  }

/* ************************************************************************ */

// Specific member functions (inherited from PreOrderMappableContainer)

  template<typename Data>
  void List<Data>::MapPreOrder(MapFunctor functor, void* parametro) {

    MapPreOrder(functor, parametro, head);

  }

/* ************************************************************************ */

// Specific member functions (inherited from PostOrderMappableContainer)

  template<typename Data>
  void List<Data>::MapPostOrder(MapFunctor functor, void* parametro) {

    MapPostOrder(functor, parametro, head);

  }

/* ************************************************************************ */

// Specific member functions (inherited from FoldableContainer)

  template<typename Data>
  void List<Data>::Fold(FoldFunctor functor, const void* parametro, void* accumulatore) const {

    FoldPreOrder(functor, parametro, accumulatore);

  }

/* ************************************************************************ */

// Specific member functions (inherited from PreOrderFoldableContainer)

  template<typename Data>
  void List<Data>::FoldPreOrder(FoldFunctor functor, const void* parametro, void* accumulatore) const {

    FoldPreOrder(functor, parametro, accumulatore, head);

  }

/* ************************************************************************ */

// Specific member functions (inherited from PostOrderFoldableContainer)

template<typename Data>
void List<Data>::FoldPostOrder(FoldFunctor functor, const void* parametro, void* accumulatore) const {

  FoldPostOrder(functor, parametro, accumulatore, head);

}


/* ************************************************************************ */
  //Funzioni ausiliarie

  //Map

  template <typename Data>
  void List<Data>::MapPreOrder(MapFunctor functor, void* parametro, Node* nodoCurr) {

    if (nodoCurr != nullptr) {
      functor(nodoCurr->element, parametro);
      MapPreOrder(functor, parametro, nodoCurr->next);
    }

  }

  template <typename Data>
  void List<Data>::MapPostOrder(MapFunctor functor, void* parametro, Node* nodoCurr) {

    if (nodoCurr != nullptr) {
      MapPostOrder(functor, parametro, nodoCurr->next);
      functor(nodoCurr->element, parametro);
    }

  }

  //Fold

  template <typename Data>
  void List<Data>::FoldPreOrder(FoldFunctor functor, const void* parametro, void* accumulatore, Node* nodoCurr) const {

    if (nodoCurr != nullptr) {
      functor(nodoCurr->element, parametro, accumulatore);
      FoldPreOrder(functor, parametro, accumulatore, nodoCurr->next);
    }

  }

  template <typename Data>
  void List<Data>::FoldPostOrder(FoldFunctor functor, const void* parametro, void* accumulatore, Node* nodoCurr) const {

    if (nodoCurr != nullptr) {
      FoldPostOrder(functor, parametro, accumulatore, nodoCurr->next);
      functor(nodoCurr->element, parametro, accumulatore);
    }

  }

}
