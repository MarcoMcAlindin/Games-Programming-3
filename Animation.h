#pragma once
#include "pch.h"
#include "Bone.h"
#include "Model.h"

//Struct to conatin data collected with assimp
struct AssimpNodeData
{
    glm::mat4 transformation;
    std::string name;
    int childrenCount;
    std::vector<AssimpNodeData> children;
};

class Animation
{
public:

    /*Public Variables
    ----------------------*/
    float m_Duration;
    float m_animationSpeed;
    int m_TicksPerSecond;
    std::vector<Bone> m_Bones;
    AssimpNodeData m_RootNode;
    std::unordered_map<std::string, BoneData> m_BoneInfoMap;

    

    /*Public Methods
    ----------------------*/

    //Constructor and Destructor
    Animation() = default;
    Animation(const std::string& animationPath, std::shared_ptr<Model> model);
    ~Animation();


    //Find bone
    Bone* FindBone(const std::string & name);

    //Getters
    inline float GetTicksPerSecond() { return m_TicksPerSecond; }
    inline float GetDuration() { return m_Duration; }
    inline const AssimpNodeData& GetRootNode() { return m_RootNode; }
    inline const std::unordered_map<std::string, BoneData>& GetBoneIDMap() { return m_BoneInfoMap; }


private:
   
    /*Private Variables
    ----------------------*/


    /*Private Methods
    ----------------------*/
    void ReadHeirarchyData(AssimpNodeData& dest, const aiNode* src);

    glm::mat4 ConvertMatrixToGLMFormat(const aiMatrix4x4& from);

    void SetUpBones(const aiAnimation* animation, Model& model);
};

