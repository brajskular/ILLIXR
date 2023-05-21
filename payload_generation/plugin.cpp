//this code decouples mesh compression from InfiniTAM, this receives the obj file from InfiniTAM and performs draco compression on it and publishes in compressed draco format
#include "common/plugin.hpp"
#include "common/switchboard.hpp"
#include "common/data_format.hpp"
#include "common/relative_clock.hpp"
#include "common/phonebook.hpp"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include "illixr_ipc.pb.h"
//decouple payload generation from ipc server
//ipc server should be a thread loop that constantly listen for new connection and grab the latest payload generated by this plugin
using namespace ILLIXR;
class PayloadGen : public plugin {
    public:
        PayloadGen(std::string name_, phonebook* pb_)
            : plugin{name_, pb_}
        , sb{pb->lookup_impl<switchboard>()}
        //, _m_uncompressed_mesh{sb->get_reader<mesh_type>("original_scene")}
        , _m_uncompressed_mesh{sb->get_reader<mesh_demo_type>("original_scene")}
        , _m_payload{sb->get_writer<payload_type>("mesh_payload")}
        {
            face_count=0;
            vertex_count=0;
            //test
            //payload = new ILLIXRIPC::IPCPayload;
            //std::string name = "mesh.objp";
            //std::ifstream file(name, std::ios::in);
            //std::stringstream buffer;
            //buffer << file.rdbuf();
            //payload->ParseFromString(buffer.str());
            //std::string payload_msg;
            //payload->SerializeToString(&payload_msg);
            //std::string msgSize = std::to_string(payload_msg.size());
            //payload_msg.insert(msgSize.size(), 10 - msgSize.size(), ' ');
            //payload_msg = msgSize + payload_msg;
            //_m_payload.put(_m_payload.allocate<payload_type>(payload_type{payload_msg, 1}));
            //printf("single payload generated\n"); 
            //delete payload;
            
            sb->schedule<mesh_demo_type>(id,"original_scene",[&](switchboard::ptr<const mesh_demo_type> datum, std::size_t){ 
                    this->ProcessFrame(datum);
            });
        }

        void ProcessFrame(switchboard::ptr<const mesh_demo_type> datum)
        {
            printf("===========Payload Generation for mesh  %d=========================\n", datum->id);
               //TODO Copy the payload generation from Sainath
               
               //std::vector<char> line;
               payload = new ILLIXRIPC::IPCPayload;
               ILLIXRIPC::Mesh* ipcMesh = payload->add_meshes();
               for(unsigned i=0; i< datum->index_x.size(); ++i)
               {
                    ILLIXRIPC::Vector3* ipcVertex = ipcMesh->add_vertices();
                    ipcVertex->set_x(datum->index_x[i]);
                    ipcVertex->set_y(datum->index_y[i]);
                    ipcVertex->set_z(datum->index_z[i]);
                    ILLIXRIPC::Color* ipcColor = ipcMesh->add_vertexcolors();
                    //TODO color is between 0-1 (divide by 255)
                    
                    //ipcColor->set_r(((datum->color_r[i])/255.0)*0.3);
                    //ipcColor->set_g(((datum->color_g[i])/255.0)*0.3);
                    //ipcColor->set_b(((datum->color_b[i])/255.0)*0.3);
                    //printf("r: %d, g: %d, b: %d\n", datum->color_r[i], datum->color_g[i], datum->color_b[i]);
                    //ipcColor->set_r(datum->color_r[i]);
                    //ipcColor->set_g(datum->color_g[i]);
                    //ipcColor->set_b(datum->color_b[i]);
                    ipcColor->set_r(datum->color_r[i]/255.0);
                    ipcColor->set_g(datum->color_g[i]/255.0);
                    ipcColor->set_b(datum->color_b[i]/255.0);

                    //add normal
                    ILLIXRIPC::Vector3* ipcNormal_1 = ipcMesh->add_normals();
                    ipcNormal_1->set_x(datum->normal_x[i]);
                    ipcNormal_1->set_y(datum->normal_y[i]);
                    ipcNormal_1->set_z(datum->normal_z[i]);
               }
               for(unsigned j=0; j<datum->face_1.size(); ++j)
               {
                    ipcMesh->add_faces(datum->face_1[j]);
                    ipcMesh->add_faces(datum->face_2[j]);
                    ipcMesh->add_faces(datum->face_3[j]);
                    
               }

               //performs serializeMessage() in the IPC server
               //std::string name = "mesh.objp";
               //readPayloadFromFile(name, payload);
               //ILLIXRIPC::Mesh* mesh = payload->add_meshes();
               //std::cout<<"datum path: "<<datum->path<<std::endl;
               //std::ifstream file(datum->path, std::ios::in);
               //std::stringstream buffer;
               //buffer << file.rdbuf();
               //file.close();


               //std::string line;
               //std::string type;

               //while (std::getline(buffer, line))
               //{
               //    std::istringstream iss(line);
               //    iss >> type;    
               //    if (type == "v")
               //    {
               //        float x, y, z;
               //        iss >> x >> y >> z; 
               //        ILLIXRIPC::Vector3* vertex = mesh->add_vertices();
               //        vertex->set_x(x); vertex->set_y(y); vertex->set_z(z);
               //    }
               //    else if (type == "vn")
               //    {
               //        float x, y, z;
               //        iss >> x >> y >> z;            
               //        ILLIXRIPC::Vector3* normal = mesh->add_normals();
               //        normal->set_x(x); normal->set_y(y); normal->set_z(z);
               //    }
               //    else if (type == "f")
               //    {
               //        std::string faceData;           
               //        iss >> faceData;                
               //        mesh->add_faces(stoi(faceData.substr(0, faceData.find("/"))) - 1);
               //        iss >> faceData;
               //        mesh->add_faces(stoi(faceData.substr(0, faceData.find("/"))) - 1);
               //        iss >> faceData;
               //        mesh->add_faces(stoi(faceData.substr(0, faceData.find("/"))) - 1);
               //    }
               //}

               //payload->set_name("Mesh Vertex Count: " + std::to_string(mesh->vertices().size()));


               std::string payload_msg;
               //payload->set_name("generated payload");
               payload->SerializeToString(&payload_msg);
               //std::cout<<"payload: "<<payload->DebugString()<<std::endl;
               
               std::string msgSize = std::to_string(payload_msg.size());
               std::cout<<"payload size: "<<msgSize<<std::endl;
               msgSize.insert(msgSize.size(), 10 - msgSize.size(), ' ');
               payload_msg = msgSize + payload_msg;
                
               //std::cout<<"payload msg: "<< payload_msg<<std::endl;

               //send to switchboard
               _m_payload.put(_m_payload.allocate<payload_type>(payload_type{payload_msg, datum->id}));
               printf("payload for %u generated\n", datum->id); 
               delete payload;
        }
        void readPayloadFromFile(std::string filename, ILLIXRIPC::IPCPayload* payload)
        {        
            auto start = std::chrono::high_resolution_clock::now();

            std::ifstream file(filename, std::ios::in);
            std::stringstream buffer;
            buffer << file.rdbuf();
            payload->ParseFromString(buffer.str());

            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);

            std::cout << "File " + filename + " " + "read in " + std::to_string(duration.count()) + "ms" << std::endl;
            // std::cout << payload->DebugString() << std::endl;

            file.close();
        }

        virtual ~PayloadGen() override{
        }

    private:
        //ILLIXR related variables
        const std::shared_ptr<switchboard> sb;
        switchboard::reader<mesh_demo_type> _m_uncompressed_mesh;
        switchboard::writer<payload_type> _m_payload;
        ILLIXRIPC::IPCPayload* payload;

        unsigned vertex_count;
        unsigned face_count;
};

PLUGIN_MAIN(PayloadGen)
