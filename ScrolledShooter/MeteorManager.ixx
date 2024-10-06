export module MeteorManager;

export class MeteorManager {
private:
    float _spawnTime;
    float _lastSpawnTime;
public:
    MeteorManager()
        : _spawnTime(5.0f)
        , _lastSpawnTime(0.0f)
    {}

    void Update();
};