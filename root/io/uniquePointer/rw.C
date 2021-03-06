#include "classes.h"

void printHistoInfo(TH1F* h, const char* meta) {
   cout << "[" << meta << "]"<< " Histogram "
        << h->GetName() << " information:\n"
        << " - Entries: " << h->GetEntries() << endl
        << " - Mean: " << h->GetMean() << endl
        << " - STD Deviation: " << h->GetRMS() << endl;

}

void w(const char* filename) {
   cout << "Writing " << filename << endl;

   TH1F meansPtr ("meansPtr","meansPtr",64, -4, 4);
   TH1F meansUPtr ("meansUPtr","meansUPtr",64, -4, 4);
   TH1F meansUPtr1 ("meansUPtr1","meansUPtr1",64, -4, 4);
   TH1F meansUPtr2 ("meansUPtr2","meansUPtr2",64, -4, 4);
   TH1F meansUPtr3 ("meansUPtr3","meansUPtr3",64, -4, 4);   

   std::unique_ptr<TFile> f (TFile::Open(filename,"RECREATE"));
   auto a = new A("RowWise");

   printHistoInfo(a->GetHPtr(), "Write Row-wise");
   printHistoInfo(a->GetHUPtr(), "Write Row-wise");

   f->WriteObject(a, "theAInstance");

   if (strstr(filename,"root")){

      // Now a Tree
      TTree t("mytree", "mytree");
      auto b = new A("ColumnWise");
      t.Branch("theABranch",&b);
      for (auto i : ROOT::TSeqI(50)) {
         b->Randomize();
         meansPtr.Fill(b->GetHPtr()->GetMean());
         meansUPtr.Fill(b->GetHUPtr()->GetMean());
         meansUPtr1.Fill(b->GetHUPtrAt(0)->GetMean());
         meansUPtr2.Fill(b->GetHUPtrAt(1)->GetMean());
         meansUPtr3.Fill(b->GetHUPtrAt(2)->GetMean());
         
         t.Fill();
      }
      printHistoInfo(&meansPtr, "Write Column-wise");
      printHistoInfo(&meansUPtr, "Write Column-wise");
      printHistoInfo(&meansUPtr1, "Write Column-wise 1");
      printHistoInfo(&meansUPtr2, "Write Column-wise 2");
      printHistoInfo(&meansUPtr3, "Write Column-wise 3");      
      t.Write();
   }


   delete a;
}

void r(const char* filename) {
   cout << "Reading " << filename << endl;

   TH1F meansPtr ("meansPtr","meansPtr",64, -4, 4);
   TH1F meansUPtr ("meansUPtr","meansUPtr",64, -4, 4);
   TH1F meansUPtr1 ("meansUPtr1","meansUPtr1",64, -4, 4);
   TH1F meansUPtr2 ("meansUPtr2","meansUPtr2",64, -4, 4);
   TH1F meansUPtr3 ("meansUPtr3","meansUPtr3",64, -4, 4);

   std::unique_ptr<TFile> f (TFile::Open(filename));
   auto a = (A*) f->Get("theAInstance");
   printHistoInfo(a->GetHPtr(), "Read Row-wise");
   printHistoInfo(a->GetHUPtr(), "Read Row-wise");
   for (auto i : {0,1,2}) {
      printHistoInfo(a->GetHUPtrAt(i),(std::string("Read Row-wise ")+std::to_string(i)).c_str());
   }

   if (strstr(filename,"root")){
      TTreeReader tr("mytree", f.get());
      TTreeReaderValue<A> myA(tr, "theABranch");

      while (tr.Next()) {
         auto mean = myA->GetHPtr()->GetMean();
         meansPtr.Fill(mean);
         mean = myA->GetHUPtr()->GetMean();
         meansUPtr.Fill(mean);
         mean = myA->GetHUPtrAt(0)->GetMean();
         meansUPtr1.Fill(mean);
         mean = myA->GetHUPtrAt(1)->GetMean();
         meansUPtr2.Fill(mean);
         mean = myA->GetHUPtrAt(2)->GetMean();
         meansUPtr3.Fill(mean);
      }
      printHistoInfo(&meansPtr, "Read Column-wise");
      printHistoInfo(&meansUPtr, "Read Column-wise");
      printHistoInfo(&meansUPtr1, "Read Column-wise 1");
      printHistoInfo(&meansUPtr2, "Read Column-wise 2");
      printHistoInfo(&meansUPtr3, "Read Column-wise 3");
   }

}

int rw(bool write = true){

   auto c = TClass::GetClass("A");
   auto si = c->GetStreamerInfo();
   // Here the output

   std::vector<const char*> filenames {"out.root"};//, "out.xml"};
   for (auto filename : filenames){
      if (write) w(filename);
      r(filename);
   }
   return 0;
}
