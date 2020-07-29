#ifndef _SKETCH_
#define _SKETCH_

//======== parameter ===========
#define ListLength 15

class Sketch
{
private:
  int Hashcount;
  int Kmemory;
  int _entropy;
  // Sketch池
public:
  bool _sketchisempty;
  Sketch(/* args */);
  ~Sketch();
  int getEntropy() { return _entropy; }
  void setEntropy(int ent) { _entropy = ent; }
  int getHashCount() { return Hashcount; }
  int getKmemoryCount() { return Kmemory; }

  int getNij() { return 0; }
};

class SketchList : public Sketch
{
public:
  Sketch _sketchL[ListLength];

public:
  SketchList();
  ~SketchList();
  void updateSketchList();
  Sketch *getSketchList();
};

#endif