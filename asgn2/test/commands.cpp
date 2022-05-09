
#include "commands.h"
#include "debug.h"
#include "util.h"

#include <sstream>      // for sstream to convert string to number.
#include <iomanip>      // for std::setw(), std::left, std::right.
#include <queue>
const command_hash cmd_hash {
   {"cat"   , fn_cat   },  // DONE
   {"cd"    , fn_cd    },  // DONE
   {"echo"  , fn_echo  },  // DONE
   {"exit"  , fn_exit  },  // DONE
   {"ls"    , fn_ls    },  // DONE
   {"lsr"   , fn_lsr   },  // DONE
   {"make"  , fn_make  },  // DONE
   {"mkdir" , fn_mkdir },  // DONE
   {"prompt", fn_prompt},  // DONE
   {"pwd"   , fn_pwd   },  // DONE
   {"rm"    , fn_rm    },  // DONE
   {"rmr"   , fn_rmr   },  // DONE
};

// Helper function

// Get the absolute pathname of inode
// Example:
//    get_pathname(state.get_cwd()) => "/dir1/dir2"
string get_pathname(inode_ptr inode);           

inode_ptr get_inode(inode_ptr root_inode, string pathname); 

// Display entry in specific format.
void ls_entry(auto& entry);   


void pre_order(inode_ptr inode);


void post_order(inode_ptr inode);


// pathname should be an absolute path
inode_ptr get_inode(inode_ptr root_inode, string pathname){
   wordvec paths = split(pathname, "/");
   inode_ptr target_inode {root_inode};
   for(size_t i = 0; i < paths.size(); i++){
      const auto& dirents = target_inode->get_dirents();
      bool found = false;
      for (const auto& entry: dirents) {
         if(entry.first == paths[i]){
            target_inode = entry.second;
            found = true;
            break;
         }
      }
      if(found == false){
         return nullptr;
      }
   }
   return target_inode;
}

command_fn find_command_fn (const string& cmd) {
   // Note: value_type is pair<const key_type, mapped_type>
   // So: iterator->first is key_type (string)
   // So: iterator->second is mapped_type (command_fn)
   DEBUGF ('c', "[" << cmd << "]");
   const auto result {cmd_hash.find (cmd)};
   if (result == cmd_hash.end()) {
      throw command_error (cmd + ": no such command");
   }
   return result->second;
}

command_error::command_error (const string& what):
            runtime_error (what) {
}

int exit_status_message() {
   int status {exec::status()};
   cout << exec::execname() << ": exit(" << status << ")" << endl;
   return status;
}

void fn_cat (inode_state& state, const wordvec& words) {
   if (words.size() != 2){    // program: words[0], pathname: words[1];
      throw command_error ("Usage: cat <pathname>");
      exec::status(1);
      return;
   }

   // words[1] is pathname, have 4 conditions:
   //    1. words[1] = "path/to/dir"
   //    2. words[1] = "path/to/file"
   //    3. words[1] = "/.../path/to/dir"
   //    4. words[1] = "/.../path/to/file"   

   string pathname = words[1];
   if(words[1][0] != '/'){ 
      pathname = (get_pathname(state.get_cwd()) == "/" ? 
      "" : get_pathname(state.get_cwd())) + "/" + pathname;
   }
   inode_ptr target_inode = get_inode(state.get_root(), pathname);
   if(target_inode == nullptr){
      throw command_error ("cat: "+ 
      pathname+": No such file or directory");
      exec::status(1);
      return;
   }
   if(target_inode->type() == file_type::DIRECTORY_TYPE){
      throw command_error ("cat: "+ 
      pathname+": can not cat a dir");
      exec::status(1);
      return;
   }
   auto& file_ptr = target_inode->get_contents();
   for(auto& data: file_ptr->readfile()){
      cout << data;
   }
   cout << endl;
}

void fn_cd (inode_state& state, const wordvec& words) {
   
   if(words.size() > 2){
      throw command_error ("cd: Usage: cd [todir]");
      exec::status(1);
      return;
   }

   if(words.size() == 1 || words[1] == "/"){
      state.set_cwd(state.get_root());
      return;
   }
   string target_pathname = words[1];
   if(words[1][0] != '/'){
      target_pathname = (get_pathname(state.get_cwd()) == "/" ? "" 
      : get_pathname(state.get_cwd())) + "/" + target_pathname;
   }
   string parent_pathname = "";
   wordvec paths = split(target_pathname,"/");
   for(size_t i = 0; i < paths.size() - 1; i++){
      parent_pathname+="/"+paths[i];
   }
   inode_ptr parent_inode=get_inode(state.get_root()
   , parent_pathname);
   if(parent_inode == nullptr){
      throw command_error ("cd: "+ parent_pathname +
       ": "+"file does not exist");
      exec::status(1);
      return;
   }
   inode_ptr target_inode = get_inode
   (state.get_root(), target_pathname);
   if(target_inode == nullptr ||
    target_inode->type() == file_type::PLAIN_TYPE){
      throw command_error ("cd: "+ target_pathname
      + ": can not cd ");
      exec::status(1);
      return;
   }

   state.set_cwd(target_inode);
}

void fn_echo (inode_state& state, const wordvec& words) {
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   cout << word_range (words.cbegin() + 1, words.cend()) << endl;
}

void fn_exit (inode_state& state, const wordvec& words) {
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   std::stringstream ss;
   int status = 0;
   if(words.size() == 2){
      bool non_numeric = false;
      for(size_t i = 0 ; i < words[1].size(); i++){
         if(words[1][i]<'0' || words[1][i]>'9'){
            status = 127;
            non_numeric = true;
            break;
         }
      }
      if(non_numeric == false){
         ss << words[1];
         ss >> status;
      }else{
         status = 127;
      }
   }
   exec::status(status);
   throw ysh_exit();
}

// Helper function
void ls_entry(auto& entry){
   cout << std::right << std::setw(6)  << entry.second->get_inode_nr() ;
   cout << "  ";
   cout << std::right << std::setw(6) << entry.second->size();
   cout << "  " ;
   cout << entry.first;
   if(entry.second->type() == file_type::DIRECTORY_TYPE){
      cout << "/";
   }
   cout << endl;
}

void fn_ls (inode_state& state, const wordvec& words) {
   string cwd_pathname = get_pathname(state.get_cwd());
   string target_pathname = "";
   if(words.size() == 1){
      target_pathname = cwd_pathname;
   }else if(words.size() >= 2 && words[1][0] != '/'){
      target_pathname = 
      (cwd_pathname == "/" ? "" : cwd_pathname) + "/" + words[1];
   }else if(words.size() >= 2 && words[1][0] == '/') {
      target_pathname = words[1];
   }
   
   inode_ptr target_inode = 
   get_inode(state.get_root(), target_pathname);
   
   cout << target_pathname << ":" << endl;
   const auto& dirents = target_inode->get_dirents();
   for (const auto& entry: dirents) {
      ls_entry(entry);
   }
}

void fn_lsr (inode_state& state, const wordvec& words) {
   if (words.size() > 2){
      throw command_error ("lsr: Usage: lsr [pathname]");
      exec::status(1);
      return;
   }
   string pathname = words.size()==1 ? "." : words[1];
   if(words[1][0] != '/'){
      pathname = (get_pathname(state.get_cwd()) == "/" ? "":
      get_pathname(state.get_cwd()))  + "/" + pathname;
   }
   inode_ptr target_inode = get_inode(state.get_root(), pathname);
   if(target_inode == nullptr){
      throw command_error ("lsr: " + pathname + ": does not exis");
      exec::status(1);
      return;
   }
   if(target_inode->type() == file_type::PLAIN_TYPE){
      throw command_error ("lsr: "+ pathname+
      ": can not run lsr on a plain file");
      exec::status(1);
      return;
   }

   pre_order(target_inode);
}


void pre_order(inode_ptr inode){
   // check filetype
   if(inode->type()==file_type::PLAIN_TYPE){
      return;
   }

   // ls all entry on current inode.
   cout << get_pathname(inode) << ":" << endl;
   const auto& dirents = inode->get_dirents();
   for (const auto& entry: dirents) {
      ls_entry(entry);
   }

   // recursive run on all entries.
   for(const auto& entry : dirents){
      if(entry.first != "." && entry.first != ".."){
         pre_order(entry.second);
      }
   }
}

void fn_make (inode_state& state, const wordvec& words) {
   //if only make command
   if(words.size() <= 1){
      throw command_error ("make: Usage: make <pathname> [data]");
      exec::status(1);
      return;
   }

   // words[1] is pathname, have 4 conditions:
   //    1. words[1] = "path/to/dir"
   //    2. words[1] = "path/to/file"
   //    3. words[1] = "/.../path/to/dir"
   //    4. words[1] = "/.../path/to/file"   
   string target_pathname = words[1];   // condition 3, 4
   if(words[1][0] != '/'){       // condition 1, 2
      target_pathname = (get_pathname(state.get_cwd()) == "/" ? "" 
      : get_pathname(state.get_cwd())) + "/" + target_pathname;
   }
   string parent_pathname = "";
   wordvec paths = split(target_pathname,"/");
   for(size_t i = 0; i < paths.size() - 1; i++){
      parent_pathname += "/" + paths[i];
   }
   inode_ptr parent_inode = 
   get_inode(state.get_root(), parent_pathname);
   if(parent_inode == nullptr){
      throw command_error ("make: " + 
      parent_pathname + ": doesn't exist");
      exec::status(1);
      return;
   }
   inode_ptr target_inode = 
   get_inode(state.get_root(), target_pathname);
   if(target_inode != nullptr && target_inode->type() == 
   file_type::DIRECTORY_TYPE){
      throw command_error ("make: " + 
      target_pathname + ": is a directory");
      exec::status(1);
      return;
   }

   directory_entries& parent_dirents = parent_inode->get_dirents();
   string filename = paths[paths.size() - 1];
   inode_ptr fileinode {nullptr};
   for (const auto& entry: parent_dirents) {
      if(entry.first == filename){
         fileinode = entry.second;
         break;
      }
   }
   if(fileinode == nullptr){
      fileinode = make_shared<inode> (file_type::PLAIN_TYPE);
      parent_dirents[filename] = fileinode;
   }

   wordvec newdata;
   for(size_t i = 2; i < words.size(); i++){
      newdata.push_back(words[i]);
   }
   // function write handle the filetype, and overwrite plainfile
   fileinode->write(newdata);
}

void fn_mkdir (inode_state& state, const wordvec& words) {
   if(words.size() != 2){
      throw command_error ("mkdir: Usage: mkdir <dir_name>");
      exec::status(1);
      return;
   }

   // words[1] is pathname, have 4 conditions:
   //    1. words[1] = "path/to/dir"
   //    2. words[1] = "path/to/file"
   //    3. words[1] = "/.../path/to/dir"
   //    4. words[1] = "/.../path/to/file"   
   string target_pathname = words[1];   // condition 3, 4
   if(words[1][0] != '/'){       // condition 1, 2
      target_pathname = (get_pathname(state.get_cwd()) == "/" ? "" :
       get_pathname(state.get_cwd())) + "/" + target_pathname;
   }
   string parent_pathname = "";
   wordvec paths = split(target_pathname,"/");
   for(size_t i = 0; i < paths.size() - 1; i++){
      parent_pathname += "/" + paths[i];
   }
   inode_ptr parent_inode=get_inode(state.get_root(), parent_pathname);
   if(parent_inode == nullptr){
      throw command_error ("mkdir: " + 
      parent_pathname + ": doesn't exist");
      exec::status(1);
      return;
   }
   inode_ptr target_inode=get_inode(state.get_root(), target_pathname);
   if(target_inode != nullptr){
      throw command_error ("mkdir: " + 
      target_pathname + ": already exist");
      exec::status(1);
      return;
   }
   
   string dirname = paths[paths.size() - 1];
   
   inode_ptr dirinode = make_shared<inode> (file_type::DIRECTORY_TYPE);
   directory_entries& dir_dirents = dirinode->get_dirents();
   
   dir_dirents["."] = dirinode;
   dir_dirents[".."] = parent_inode;

   directory_entries& parent_dirents = parent_inode->get_dirents();
   parent_dirents[dirname] = dirinode;
}

void fn_prompt (inode_state& state, const wordvec& words) {
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if(words.size() != 2){
      throw command_error ("prompt: Usaeg: prompt <prompt>");
      exec::status(1);
      return;
   }
   state.set_prompt(words[1]+" ");
}

string get_pathname(inode_ptr inode){
   string result = "";
   inode_ptr current_inode = inode;
   directory_entries current_dirents = current_inode->get_dirents();
   inode_ptr parent_inode = current_dirents.find("..")->second;
   directory_entries parent_dirents = parent_inode->get_dirents();
   if(current_inode == parent_inode){
      result = "/";
      return result;
   }
   while(current_inode != parent_inode){
      for (const auto& entry: parent_dirents) {
         if(entry.second == current_inode){
            result.insert(0, entry.first);
            result.insert(0, "/");
            break;
         }
      }
      current_inode = parent_inode;
      current_dirents = parent_dirents;
      parent_inode = current_dirents.find("..")->second;
      parent_dirents = parent_inode->get_dirents();
   }
   return result;
}

void fn_pwd (inode_state& state, const wordvec& words) {
   // string pathname = words[1];
   // inode_ptr inode;
   // if(words.size()>1){
   //    inode = get_inode(state.get_cwd(), pathname);
   //    pathname = get_pathname(inode);
   // }
   // else{
   //    pathname = get_pathname(state.get_cwd());
   // }
   // cout << pathname << endl;
   if(words.size() != 1){
      throw command_error ("pwd: Usage: pwd" );
      exec::status(1);
      return;
   }
   cout << get_pathname(state.get_cwd()) << endl;
}

void fn_rm (inode_state& state, const wordvec& words) {
   if(words.size() != 2){
      throw command_error ("rm: Usage: rm <pathname>");
      exec::status(1);
      return;
   }

   // words[1] is pathname, have 4 conditions:
   //    1. words[1] = "path/to/dir"
   //    2. words[1] = "path/to/file"
   //    3. words[1] = "/.../path/to/dir"
   //    4. words[1] = "/.../path/to/file"   
   string target_pathname = words[1];   // condition 3, 4
   if(words[1][0] != '/'){       // condition 1, 2
      target_pathname = (get_pathname(state.get_cwd()) == "/" ? "" 
      : get_pathname(state.get_cwd())) + "/" + target_pathname;
   }
   string parent_pathname = "";
   wordvec paths = split(target_pathname,"/");
   for(size_t i = 0; i < paths.size() - 1; i++){
      parent_pathname += "/" + paths[i];
   }
   inode_ptr parent_inode=get_inode(state.get_root(), parent_pathname);
   if(parent_inode == nullptr){
      throw command_error ("rm: "+
      parent_pathname+ ": does not exist");
      exec::status(1);
      return;
   }
   inode_ptr target_inode=get_inode(state.get_root(), target_pathname);
   if(target_inode == nullptr){
      throw command_error ("rm: "+
      target_pathname + ": does not exist");
      exec::status(1);
      return;
   }
   string pathname = paths[paths.size() - 1];
   
   directory_entries& parent_dirents = parent_inode->get_dirents();
   parent_dirents.erase(pathname);
}

void fn_rmr (inode_state& state, const wordvec& words) {
   if (words.size() > 2){
      throw command_error ("rmr: Usage: rmr [pathname]");
      exec::status(1);
      return;
   }
   if(words[1] == "/"){
      post_order(state.get_root());
      auto& dirents = state.get_root()->get_dirents();
      dirents.clear();
      state.set_cwd(nullptr);
      state.set_root(nullptr);
      return;
   }
   string pathname = words.size()==1 ? "." : words[1];
   if(words[1][0] != '/'){
      pathname = (get_pathname(state.get_cwd()) == "/" ? "" 
      : get_pathname(state.get_cwd())) + "/" + pathname;
   }
   inode_ptr target_inode = get_inode(state.get_root(), pathname);
   if(target_inode == nullptr){
      throw command_error ("rmr: " + 
      pathname+": does not exist");
      exec::status(1);
      return;
   }
   if(target_inode->type() == file_type::PLAIN_TYPE){
      throw command_error ("rmr: " + 
      pathname+": can not run rmr on a plain file");
      exec::status(1);
      return;
   }
   inode_ptr parent_inode = target_inode->get_dirents()[".."];
   
   post_order(target_inode);

   // rm target_inode from parent.
   directory_entries& cwd_dirents = parent_inode->get_dirents();
   for(auto& entry : cwd_dirents){
      if(entry.second == target_inode &&
       entry.first != "." && entry.first != "..") {
         cwd_dirents.erase(entry.first);
      }
   }
}

void post_order(inode_ptr inode){
   // check filetype
   if(inode->type() == file_type::PLAIN_TYPE){
      return;
   }

   auto& dirents = inode->get_dirents();
   // recursive run on all entries, except "." and ".."
   for(const auto& entry : dirents){
      if(entry.first != "." && entry.first != ".."){
         post_order(entry.second);
      }
   }

   // rm all entry on current inode.
   dirents.clear();
}
