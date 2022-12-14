/*******************************************************************************
 * Copyright (c) The JETSCAPE Collaboration, 2018
 *
 * Modular, task-based framework for simulating all aspects of heavy-ion collisions
 * 
 * For the list of contributors see AUTHORS.
 *
 * Report issues at https://github.com/JETSCAPE/JETSCAPE/issues
 *
 * or via email to bugs.jetscape@gmail.com
 *
 * Distributed under the GNU General Public License 3.0 (GPLv3 or later).
 * See COPYING for details.
 ******************************************************************************/

// jetscape writer ascii class

#ifndef SOFTHADRONWRITER_H
#define SOFTHADRONWRITER_H

#include <fstream>
#include <string>

#ifdef USE_GZIP
#include "gzstream.h"
#endif

#include "JetScapeWriter.h"

using std::ofstream;

namespace Jetscape {

template<class T>  
class SoftHadronWriter : public JetScapeWriter
{

 public:

  SoftHadronWriter<T>() {};
  SoftHadronWriter<T>(string m_file_name_out);
  virtual ~SoftHadronWriter<T>();

  void Init();
  void Exec();
  
  bool GetStatus() {return output_file.good();}
  void Close() {output_file.close();}

  void Write(weak_ptr<Hadron> h);
  void WriteHeaderToFile();
  
  void Write(string s) {output_file<<s<<endl;}
  void WriteComment(string s) {output_file<<"# "<<s<<endl;}
  void WriteWhiteSpace(string s) {output_file<<s<<" ";}
  void WriteEvent(); 
  
 protected:

  T output_file; //!< Output file
  //int m_precision; //!< Output precision
  
};

typedef SoftHadronWriter<ofstream> SoftHadronWriterAscii;
#ifdef USE_GZIP
typedef SoftHadronWriter<ogzstream> SoftHadronWriterAsciiGZ;
#endif

} // end namespace Jetscape

#endif // SOFTHADRONWRITER_H
