var Post = require('../models/posts')
const mongoose = require('mongoose')

module.exports.getPosts = () => {
    return Post
            .find()
            .then(resposta => {
                return resposta
            })
            .catch(erro => {
                return erro
            })
}

module.exports.getPostsPage = pageIndex => {
    return Post
            .find()
            .sort({data:-1})
            .skip((pageIndex-1) * 10)
            .limit(10)
            .then(resposta => {
                return resposta
            })
            .catch(erro => {
                return erro
            })
}

module.exports.getPostsLen = () => {
    return Post
            .find()
            .count()
            .then(resposta => {
                return resposta
            })
            .catch(erro => {
                return erro
            })
}

module.exports.getPostID = id => {
    return Post.findOne({_id: new mongoose.Types.ObjectId(id)})
            .then(resposta => {
                return resposta
            })
            .catch(erro => {
                return erro
            })
}

module.exports.getPostPesquisa = (type, searchn, pageIndex) => {
    if (type == "nome")
    {
        const countQuery = Post.find({ nome: { $regex: searchn, $options: 'i' } }).count();
        const searchQuery = Post
                            .find({ nome: { $regex: searchn, $options: 'i' } })
                            .sort({nome:-1})
                            .skip((pageIndex-1) * 10)
                            .limit(10);
        return Promise.all([countQuery, searchQuery])
                      .then(([count, resposta]) => {
                            return { list: resposta, len: count };
                        })
                        .catch(erro => {
                          return erro;
                        });
    }
    if (type == "data")
    {
        const countQuery = Post.find({ data: { $regex: searchn, $options: 'i' } }).count();
        const searchQuery = Post
                            .find({ data: { $regex: searchn, $options: 'i' } })
                            .sort({data:-1})
                            .skip((pageIndex-1) * 10)
                            .limit(10);
        return Promise.all([countQuery, searchQuery])
                      .then(([count, resposta]) => {
                            return { list: resposta, len: count };
                        })
                        .catch(erro => {
                          return erro;
                        });
    }
}

module.exports.addPost = p => {
    p._id = new mongoose.Types.ObjectId()
    return Post.create(p)
            .then(resposta => {
                return resposta
            })
            .catch(erro => {
                return erro
            })
}

module.exports.addComment = (id, c) => {
    return Post.findOne({_id: new mongoose.Types.ObjectId(id)})
                .then((post) => {
                if (!post) {
                    console.log('Post not found');
                    return;
                }
                
                const newComment = {
                    _id: new mongoose.Types.ObjectId(),
                    username: c.nome,
                    descricao: c.coment 
                };
                
                post.coments.push(newComment);
            
                return post.save();
                })
                .then(() => {
                console.log('Comment added successfully');
                })
                .catch((err) => {
                console.error(err);
                });
}

module.exports.updatePost = p => {
    return Post.updateOne({_id:p._id}, p)
            .then(resposta => {
                return resposta
            })
            .catch(erro => {
                return erro
            })
}

module.exports.deletePost = id => {
    return Post.deleteOne({_id:id})
            .then(resposta => {
                return resposta
            })
            .catch(erro => {
                return erro
            })
}

module.exports.deleteComment = (idPost, idComment) => {
    return Post.updateOne({_id: idPost }, 
                { $pull: {"coments": {_id: idComment}}})
            .then(resposta => {
                return resposta
            })
            .catch(erro => {
                return erro
            })
}
