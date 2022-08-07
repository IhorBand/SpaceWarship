#include "GameRender.h"


GameRender* GameRender::s_instance = nullptr;

GameRender::GameRender()
{

}

GameRender* GameRender::GetInstance()
{
    if (!s_instance)
    {
        s_instance = new GameRender();
    }

    return s_instance;
}

void GameRender::Initialize(size_t windowWidth, size_t windowHeight)
{
    GameRender& instance = *GetInstance();
    instance._quality = 1.0f;
    //instance._zoom = 1.5f;
    instance._zoom = 1;
    
    instance._ratio = instance._zoom / instance._quality;
    instance._focus = sf::Vector2f(MAP_SIZE_WIDTH/2, MAP_SIZE_HEIGHT/2);
    instance._renderSize = sf::Vector2u(static_cast<uint32_t>(windowWidth * instance._quality),
        static_cast<uint32_t>(windowHeight * instance._quality));

    float bx = instance._renderSize.x / (instance._quality * instance._zoom) * 0.5f;
    float by = instance._renderSize.y / (instance._quality * instance._zoom) * 0.5f;
    instance._baseOffset = sf::Vector2f(bx, by);

    instance._renderTexture.create(instance._renderSize.x, instance._renderSize.y);
    instance._groundTexture.create(MAP_SIZE_WIDTH, MAP_SIZE_HEIGHT);

    // 2 is the layers count
    instance._vertices.resize(RenderLayer::RenderLayer_SIZE);

    GraphicsUtils::Init();
}

void GameRender::SetFocus(const sf::Vector2f& focus)
{
    GameRender& instance = *GetInstance();
    instance._focus = focus;
}

void GameRender::Clear()
{
    GameRender& instance = *GetInstance();
    
    for (std::vector<sf::VertexArray>& v : instance._vertices) 
    {
        for (sf::VertexArray& va : v)
        {
            va.clear();
        }
    }

    instance._renderTexture.clear(sf::Color::Black);
    RenderVertexArray(instance._groundQuad, instance._renderTexture, instance._groundTextureID);
}

/// Adds a quad to be rendered in the current frame
void GameRender::AddQuad(size_t textureID, const sf::VertexArray& quad, RenderLayer layer)
{
    sf::VertexArray* va(&GetInstance()->_vertices[layer][textureID]);
    va->append(quad[0]);
    va->append(quad[1]);
    va->append(quad[2]);
    va->append(quad[3]);
}

/// Loads and adds a new texture in the render engine
size_t GameRender::RegisterTexture(std::string filename, bool isRepeated)
{
    GameRender& instance = *GetInstance();

    instance._textures.push_back(sf::Texture());
    instance._textures.back().setRepeated(isRepeated);

    for (int i = 0; i < RenderLayer_SIZE; i++)
    {
        instance._vertices[i].push_back(sf::VertexArray(sf::Quads, 0));
    }

    if (instance._textures.back().loadFromFile(filename)) {
        std::cout << "Added new texture : " << filename << " with ID " << instance._textures.size() << std::endl;
    }
    else {
        std::cout << "Error : cannot load'" << filename << "'" << std::endl;
    }

    return instance._textures.size() - 1;
}

void GameRender::RenderVertexArray(const sf::VertexArray& va, sf::RenderTexture& target)
{
    sf::RenderStates states;
    GetInstance()->_translateToFocus(states.transform);

    target.draw(va, states);
}

void GameRender::RenderVertexArray(const sf::VertexArray& va, sf::RenderTexture& target, sf::RenderStates states)
{
    GetInstance()->_translateToFocus(states.transform);

    target.draw(va, states);
}

void GameRender::RenderVertexArray(const sf::VertexArray& va, sf::RenderTexture& target, size_t textureID)
{
    GameRender& instance = *GetInstance();

    sf::RenderStates states;
    instance._translateToFocus(states.transform);
    states.texture = &instance._textures[textureID];
    target.draw(va, states);
}

/// Draws a vertexArray in the texture
void GameRender::_renderVertices(std::vector<sf::VertexArray>& vertices, sf::RenderTexture& target, sf::RenderStates& states)
{
    GameRender& instance = *GetInstance();

    size_t size(vertices.size());
    for (size_t i(0); i < size; ++i)
    {
        if (vertices[i].getVertexCount())
        {
            states.texture = &instance._textures[i];
            target.draw(vertices[i], states);
        }
    }
}

/// Finalizes the textures
void GameRender::Display(sf::RenderTarget* target)
{
    GameRender& instance = *GetInstance();

    sf::Transform tf;
    tf.scale(instance._quality, instance._quality);
    _translateToFocus(tf);
    sf::RenderStates states;
    states.transform = tf;

    RenderGround();

    for (int i = 0; i < RenderLayer::RenderLayer_SIZE; i++)
    {
        if (i != RenderLayer::GROUND)
        {
            instance._renderVertices(instance._vertices[i], instance._renderTexture, states);
        }
    }
    instance._renderTexture.display();

    sf::Sprite renderSprite(instance._renderTexture.getTexture());
    renderSprite.setScale(instance._ratio, instance._ratio);
    target->draw(renderSprite);
}

/// Determines if something is in the render view
bool GameRender::IsVisible(WorldEntity* entity)
{
    return IsVisible(entity->GetCoord(), 2 * CELL_SIZE);
}

bool GameRender::IsVisible(const sf::Vector2f& position, float radius)
{
    GameRender& instance = *GetInstance();

    float screenPosX = position.x - instance._focus.x;
    float screenPosY = position.y - instance._focus.y;

    return (std::abs(screenPosX) < instance._baseOffset.x + radius && std::abs(screenPosY) < instance._baseOffset.y + radius);
}

void GameRender::InitGround(size_t textureID, sf::VertexArray& quad)
{
    GameRender& instance = *GetInstance();

    instance._groundTextureID = textureID;
    instance._groundQuad = quad;
    instance._groundTexture.clear(sf::Color(0, 0, 0, 0));
}

/// Draw the ground
void GameRender::RenderGround()
{
    GameRender& instance = *GetInstance();

    sf::RenderStates states;
    instance._renderVertices(instance._vertices[RenderLayer::GROUND], instance._groundTexture, states);
    instance._groundTexture.display();

    sf::Sprite groundSprite(instance._groundTexture.getTexture());
    groundSprite.setScale(instance._quality, instance._quality);
    float tx = (instance._focus.x - instance._baseOffset.x) * instance._quality;
    float ty = (instance._focus.y - instance._baseOffset.y) * instance._quality;

    groundSprite.setPosition(-tx, -ty);
    instance._renderTexture.draw(groundSprite, states);
}

void GameRender::FadeGround()
{
    GameRender& instance = *GetInstance();

    const sf::Vector2i size(instance._groundTexture.getSize());
    sf::RectangleShape rectangle(sf::Vector2f(static_cast<float>(size.x), static_cast<float>(size.y)));
    rectangle.setFillColor(sf::Color(255, 255, 255, 255));
    instance._groundTexture.draw(rectangle, sf::BlendMultiply);
}

void GameRender::_translateToFocus(sf::Transform& transform)
{
    GameRender& instance = *GetInstance();
    transform.translate(instance._baseOffset.x - instance._focus.x, instance._baseOffset.y - instance._focus.y);
}
